/*
 * bluetooth_spp.c
 *
 *  Created on: Nov 6, 2013
 *      Author: liyixiao
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <btstack/hci_cmds.h>
#include <btstack/run_loop.h>
#include <btstack/sdp_util.h>
#include <btstack/utils.h>

#include "debug.h"
#include "hci.h"
#include "l2cap.h"
#include "rfcomm.h"
#include "sdp.h"
#include "bt_control_cc256x.h"

//#include "driver_common.h"
//#include "kernel_cfg.h"
//#include "syssvc/serial.h"
//#include "platform.h"
#include "btstack-interface.h"
#include "bluetooth_init_cc2560_2.44.c"
#include "bluetooth_init_cc2560A_2.14.c"

#define RFCOMM_SERVER_CHANNEL 1
#define HEARTBEAT_PERIOD_MS 10

static uint16_t  rfcomm_channel_id = 0;

static uint8_t   spp_service_buffer[150];

//static bd_addr_t host_addr = { 0x00, 0x07, 0x04, 0xfe, 0xfe, 0xf2 };

static timer_source_t heartbeat;

static uint8_t  *send_buffer;
static uint32_t send_buffer_sz = 0;
static uint32_t send_mtu = 0; // Max frame size for sending, > 0 to indicate that RFCOMM channel open succeeded.

static uint8_t  *spp_master_test_send_buffer;
static uint32_t spp_master_test_send_buffer_sz = 0;

#include "bluetooth_spp_master.c"

static void send_timer_handler(timer_source_t *ts){
	// Fetch when necessary
	if(send_buffer_sz == 0)
		bt_fetch_snd_buf(&send_buffer, &send_buffer_sz);

	// Try to send
	if(send_mtu > 0 && send_buffer_sz > 0) { // RFCOMM channel opened and send buffer is not empty
		uint16_t send_bytes = (send_mtu < send_buffer_sz) ? send_mtu : send_buffer_sz;
		if(!hci_is_packet_buffer_reserved() && rfcomm_send_internal(rfcomm_channel_id, send_buffer, send_bytes) == 0) { // Succeed
			send_buffer    += send_bytes;
			send_buffer_sz -= send_bytes;
		}
	}

	if (spp_master_test_send_buffer_sz == 0) rfcomm_channel_rdysend_callback(RFCOMM_CHANNEL_SPP_MASTER_TEST, &spp_master_test_send_buffer, &spp_master_test_send_buffer_sz);
	if (spp_master_test_channel_mtu > 0 && spp_master_test_send_buffer_sz > 0) {
		uint16_t send_bytes = (spp_master_test_channel_mtu < spp_master_test_send_buffer_sz) ? spp_master_test_channel_mtu : spp_master_test_send_buffer_sz;
		if(!hci_is_packet_buffer_reserved() && rfcomm_send_internal(spp_master_test_channel_id, spp_master_test_send_buffer, send_bytes) == 0) { // Succeed
			spp_master_test_send_buffer    += send_bytes;
			spp_master_test_send_buffer_sz -= send_bytes;
		}
	}

	run_loop_set_timer(ts, HEARTBEAT_PERIOD_MS);
	run_loop_add_timer(&heartbeat);
}

static void packet_handler (void * connection, uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    bd_addr_t event_addr;
    uint8_t   rfcomm_channel_nr;
    uint16_t  mtu;

    switch (packet_type) {
    case RFCOMM_DATA_PACKET:
		if (connection == SPP_MASTER_TEST_CONNECTION) {
			rfcomm_channel_receive_callback(RFCOMM_CHANNEL_SPP_MASTER_TEST, packet, size);
		} else {
//    	syslog(LOG_NOTICE, "RFCOMM_DATA_PACKET size: %d", size);
    	bt_rcv_handler(packet, size);
		}
    	break;

	case HCI_EVENT_PACKET:

		switch (packet[0]) {
		case BTSTACK_EVENT_STATE:
			// bt stack activated, get started - set local name
			if (packet[2] == HCI_STATE_WORKING) {
				hci_send_cmd(&hci_write_local_name, ev3rt_bluetooth_local_name);
			}
			break;

		case HCI_EVENT_LINK_KEY_REQUEST:
#if defined(DEBUG)
			log_info("HCI_EVENT_LINK_KEY_REQUEST \n");
#endif
			// link key request
			bt_flip_addr(event_addr, &packet[2]);
			hci_send_cmd(&hci_link_key_request_negative_reply, &event_addr);
			break;

		case HCI_EVENT_PIN_CODE_REQUEST:
			// inform about pin code request
#if defined(DEBUG)
			log_info("Please enter PIN %s on remote device\n", BLUETOOTH_PIN_CODE);
#endif
			bt_flip_addr(event_addr, &packet[2]);
            if (memcmp(spp_master_remote, event_addr, BD_ADDR_LEN) == 0) // SPP_MASTER_TEST
                hci_send_cmd(&hci_pin_code_request_reply, &event_addr, strlen(spp_master_pincode), spp_master_pincode);
            else 
                hci_send_cmd(&hci_pin_code_request_reply, &event_addr, strlen(ev3rt_bluetooth_pin_code), ev3rt_bluetooth_pin_code);
			break;

		case HCI_EVENT_COMMAND_COMPLETE:
			// Print MAC address of EV3's Bluetooth device
			if (COMMAND_COMPLETE_EVENT(packet, hci_read_bd_addr)) {
				bt_flip_addr(event_addr, &packet[6]);
                static char bd_addr_str[6*3];
                memcpy(bd_addr_str, bd_addr_to_str(event_addr), 6 * 3);
                bd_addr_str[6*3-1] = '\0';
				log_error("BT Addr: %s", bd_addr_str);
                spp_master_setup(); // init SPP master service
				break;
			}

            // Select initialization script by Link Manager Protocol (LMP) subversion
            if (COMMAND_COMPLETE_EVENT(packet, hci_read_local_version_information)) {
                // Reference: st_kim.c in ev3dev
                uint16_t version = READ_BT_16(packet, 12);
                uint16_t chip = (version & 0x7C00) >> 10;
                uint16_t min_ver = (version & 0x007F);
                uint16_t maj_ver = (version & 0x0380) >> 7;
                if (version & 0x8000) maj_ver |= 0x0008;

                extern const uint8_t *cc256x_init_script;
                extern uint32_t cc256x_init_script_size;
                if (chip == 6 && maj_ver == 2 && min_ver == 31) { // CC2560
                    log_error("BT Chip: CC2560");
                    cc256x_init_script = cc2560_init_script;
                    cc256x_init_script_size = cc2560_init_script_size;
                } else { // CC2560A as default
                    if ((chip == 6 && maj_ver == 6 && min_ver == 15)) {
                        log_error("BT Chip: CC2560A");
                    } else log_error("Unknown BT HW ver 0x%x", version);
                    cc256x_init_script = cc2560A_init_script;
                    cc256x_init_script_size = cc2560A_init_script_size;
                }

                break;
            }

			break;

		case RFCOMM_EVENT_INCOMING_CONNECTION:
			// data: event (8), len(8), address(48), channel (8), rfcomm_cid (16)
			bt_flip_addr(event_addr, &packet[2]);
			rfcomm_channel_nr = packet[8];
			rfcomm_channel_id = READ_BT_16(packet, 9);
			log_info("RFCOMM channel %u requested for %s\n\r", rfcomm_channel_nr, bd_addr_to_str(event_addr));
			rfcomm_accept_connection_internal(rfcomm_channel_id); // Always accept
//			if (memcmp(event_addr, host_addr, sizeof(bd_addr_t)) == 0 || true /* TODO: Always accept */) {
//				syslog(LOG_DEBUG,
//						"[bluetooth] Accept RFCOMM connection from host.");
//				rfcomm_accept_connection_internal(rfcomm_channel_id);
//			} else {
//				syslog(LOG_WARNING,
//						"[bluetooth] Decline RFCOMM connection from unknown device %s.",
//						bd_addr_to_str(event_addr));
//				rfcomm_decline_connection_internal(rfcomm_channel_id);
//			}
			break;

		case RFCOMM_EVENT_OPEN_CHANNEL_COMPLETE:
			// data: event(8), len(8), status (8), address (48), server channel(8), rfcomm_cid(16), max frame size(16)
            log_error("RFCOMM_EVENT_OPEN_CHANNEL_COMPLETE connection %p", connection);
            if (connection == SPP_MASTER_TEST_CONNECTION) {
                if(packet[2]) log_error("RFCOMM channel open failed, status %u. WHEN SPP_MASTER_TEST_CONNECTION", packet[2]);
                spp_master_test_channel_id  = READ_BT_16(packet, 12);
				spp_master_test_channel_mtu = READ_BT_16(packet, 14);
                spp_master_state = SPP_MASTER_DONE;
				rfcomm_channel_open_callback(RFCOMM_CHANNEL_SPP_MASTER_TEST);
            }
            else if (packet[2]) {
				log_error("RFCOMM channel open failed, status %u.", packet[2]);
			} else {
				rfcomm_channel_id = READ_BT_16(packet, 12);
				mtu = READ_BT_16(packet, 14);
#if defined(DEBUG)
				log_info("RFCOMM channel open succeeded. New RFCOMM Channel ID %u, max frame size %u.", rfcomm_channel_id, mtu);
#endif
				send_mtu = mtu;

                rfcomm_channel_open_callback(RFCOMM_CHANNEL_SPP_SERVER);
			}
			break;

		case RFCOMM_EVENT_CHANNEL_CLOSED:
			if (connection == SPP_MASTER_TEST_CONNECTION) {
	            rfcomm_channel_close_callback(RFCOMM_CHANNEL_SPP_MASTER_TEST);
				spp_master_test_channel_id = 0;
				spp_master_test_channel_mtu = 0;
				// TODO: reset state?
			} else {
	            rfcomm_channel_close_callback(RFCOMM_CHANNEL_SPP_SERVER);
				send_mtu = 0;
				rfcomm_channel_id = 0;
				send_buffer_sz = 0;
			}
			break;

		default:
			//syslog(LOG_INFO, "Unresolved event packet %d", packet[0]);
			break;
		}
		break;

	default:
		break;
    }
}

#include "panu.c"

void bluetooth_spp_initialize(void){
    hci_discoverable_control(1);
    hci_set_class_of_device(0x800804); // Information + Toy + Robot, http://bluetooth-pentest.narod.ru/software/bluetooth_class_of_device-service_generator.html

    // Secure Simple Pairing configuration -> just works
    // SSP is enabled by default.
//    hci_ssp_set_enable(1);
//    hci_ssp_set_io_capability(SSP_IO_CAPABILITY_NO_INPUT_NO_OUTPUT);
//    hci_ssp_set_auto_accept(1);
//    if(BLUETOOTH_PIN_CODE != NULL)
    hci_ssp_set_enable(0);

    l2cap_init();
    l2cap_register_packet_handler(packet_handler);

    rfcomm_init();
    rfcomm_register_packet_handler(packet_handler);
    rfcomm_register_service_internal(NULL, RFCOMM_SERVER_CHANNEL, btstack_rfcomm_mtu);  // reserved channel, mtu=BT_SND_BUF_SIZE
    //rfcomm_register_service_internal(NULL, RFCOMM_SERVER_CHANNEL, BT_SND_BUF_SIZE);  // reserved channel, mtu=BT_SND_BUF_SIZE

    // set one-shot timer
    heartbeat.process = &send_timer_handler;
    run_loop_set_timer(&heartbeat, HEARTBEAT_PERIOD_MS);
    run_loop_add_timer(&heartbeat);

    // init SDP, create record for SPP and register with SDP
    sdp_init();
    memset(spp_service_buffer, 0, sizeof(spp_service_buffer));
    service_record_item_t * service_record_item = (service_record_item_t *) spp_service_buffer;
    sdp_create_spp_service( (uint8_t*) &service_record_item->service_record, RFCOMM_SERVER_CHANNEL, "Serial Port Profile");
//    log_info("SDP service buffer size: %u\n\r", (uint16_t) (sizeof(service_record_item_t) + de_get_len((uint8_t*) &service_record_item->service_record)));
    sdp_register_service_internal(NULL, service_record_item);

    if (!(*ev3rt_bluetooth_pan_disabled)) panu_setup();
}

static const hci_uart_config_t hci_uart_config_cc256x = {
    NULL,
    115200,
    1875000,
    0
};

static void hw_err_cb() {
    log_error("!!!!BLUETOOTH HARDWARE ERROR!!!!\n");
}

void btstack_task(intptr_t unused) {
    log_debug("[bluetooth] Start main task.");

    run_loop_init(RUN_LOOP_EMBEDDED);

    // Initialize HCI
    bt_control_t             *control   = bt_control_cc256x_instance();
	hci_transport_t          *transport = hci_transport_h4_dma_instance();
	hci_uart_config_t        *config    = &hci_uart_config_cc256x;
	const remote_device_db_t *db        = &remote_device_db_memory;
	hci_init(transport, config, control, db);
    hci_set_hardware_error_callback(hw_err_cb);

    // Initialize SPP (Serial Port Profile)
    bluetooth_spp_initialize();

	// Power on
	bt_control_cc256x_enable_ehcill(0);
	hci_power_control(HCI_POWER_ON);

    run_loop_execute();
#if 0 // Code for debugging
        while(1) {
//        	bluetooth_uart_isr();
        	embedded_execute_once();
//        			if(rx_size > 0 && (UART2.IIR_FCR & 0x4)) // TODO: dirty hack
//        				AINTC.SISR = UART2_INT;
        	tslp_tsk(1); // TODO: Use interrupt instead of sleeping. -- ertl-liyixiao
        }
#endif
}
