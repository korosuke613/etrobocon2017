#include "sdp_query_rfcomm.h"
#include "rfcomm.h"
#include "sdp.h"

#define SPP_MASTER_TIMER_PERIOD_MS (100)

#define SPP_MASTER_TEST_CONNECTION ((void*)0xdeadbeef)
static uint16_t spp_master_test_channel_id = 0;
static uint16_t spp_master_test_channel_mtu = 0;

typedef enum {
//    SPP_MASTER_TEST,
    SPP_MASTER_IDLE,
    SPP_MASTER_BUSY,
    SPP_MASTER_OPEN,
    SPP_MASTER_SDP,
    SPP_MASTER_DONE,
} spp_master_state_t;

static spp_master_state_t spp_master_state = SPP_MASTER_IDLE;
static bd_addr_t          spp_master_remote;
static char               spp_master_pincode[17];

typedef enum {
    W4_SDP_RESULT,
    W4_SDP_COMPLETE,
    W4_RFCOMM_CHANNEL,
    DONE
} state_t;
static state_t state = W4_SDP_RESULT;
static uint8_t  channel_nr = 0;
//static bd_addr_t remote = {0xD0, 0x07, 0x90, 0x49, 0xCB, 0x93};

#define spp_service_name_prefix "Serial Port"
static void handle_found_service(char * name, uint8_t port){
    log_error("APP: Service name: '%s', RFCOMM port %u\n", name, port);

    if (strncmp(name, spp_service_name_prefix, strlen(spp_service_name_prefix)) != 0) return;

    log_error("APP: matches requested SPP Service Name\n");
    channel_nr = port;
    state = W4_SDP_COMPLETE;
}

static void handle_query_rfcomm_event(sdp_query_event_t * event, void * context){
    sdp_query_rfcomm_service_event_t * ve;

    switch (event->type){
        case SDP_QUERY_RFCOMM_SERVICE:
            ve = (sdp_query_rfcomm_service_event_t*) event;
            handle_found_service((char*) ve->service_name, ve->channel_nr);
            break;
        case SDP_QUERY_COMPLETE:
            if (state != W4_SDP_COMPLETE){
                log_error("Requested SPP Service %s not found \n", spp_service_name_prefix);
                spp_master_state = SPP_MASTER_IDLE;
                break;
            }
            // connect
            log_error("Requested SPP Service found, creating RFCOMM channel\n");
            state = W4_RFCOMM_CHANNEL;
            rfcomm_create_channel_internal(SPP_MASTER_TEST_CONNECTION, spp_master_remote, channel_nr);
            break;
        default:
            break;
    }
}

static timer_source_t spp_master_timer;

#if BD_ADDR_LEN != 6
#error BD_ADDR_LEN must be 6.
#endif
uint8_t spp_master_test_start_connection(const uint8_t remote_addr[6], const char *pin) {
    if (spp_master_state != SPP_MASTER_IDLE) return 0; // TODO: thread-safe
    spp_master_state = SPP_MASTER_BUSY; // TODO: use CPU lock to remove BUSY state
    memcpy(spp_master_remote, remote_addr, BD_ADDR_LEN);
    strncpy(spp_master_pincode, pin, sizeof(spp_master_pincode));
    spp_master_pincode[sizeof(spp_master_pincode) - 1] = '\0';
    spp_master_test_channel_id = 0;
    // FIXME: store pin code
    spp_master_state = SPP_MASTER_OPEN;
}

uint8_t spp_master_test_is_connecting() {
    if (spp_master_state == SPP_MASTER_DONE || spp_master_state == SPP_MASTER_IDLE) return 0;
    return 1;
}

static void spp_master_timer_handler(timer_source_t *ts) {
    if (spp_master_state == SPP_MASTER_OPEN) {
        log_error("SPP_MASTER_SDP start");
        spp_master_state = SPP_MASTER_SDP;
        sdp_query_rfcomm_channel_and_name_for_uuid(spp_master_remote, SDP_PublicBrowseGroup);
    }

	run_loop_set_timer(ts, SPP_MASTER_TIMER_PERIOD_MS);
	run_loop_add_timer(&spp_master_timer);
}

static void spp_master_setup() {
    sdp_query_rfcomm_register_callback(handle_query_rfcomm_event, NULL);
    spp_master_timer.process = spp_master_timer_handler;
    run_loop_set_timer(&spp_master_timer, SPP_MASTER_TIMER_PERIOD_MS);
    run_loop_add_timer(&spp_master_timer);
}
