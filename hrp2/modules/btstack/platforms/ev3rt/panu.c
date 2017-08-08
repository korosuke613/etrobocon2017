#include "pan.h"
#include "bnep.h"

static uint16_t bnep_cid            = 0;

static uint8_t network_buffer[BNEP_MTU_MIN];
static size_t  network_buffer_len = 0;
static uint8_t network_buffer2[BNEP_MTU_MIN];
static size_t  network_buffer_len2 = 0;

static void panu_packet_handler (void * connection, uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size)
{
    int       rc;
    uint8_t   event;
    bd_addr_t event_addr;
    bd_addr_t local_addr;
    uint16_t  uuid_source;
    uint16_t  uuid_dest;
    uint16_t  mtu;

    switch (packet_type) {
		case HCI_EVENT_PACKET:
            event = packet[0];
            switch (event) {

                /* @text BNEP_EVENT_OPEN_CHANNEL_COMPLETE is received after a BNEP connection was established or
                 * or when the connection fails. The status field returns the error code.
                 *
                 * The TAP network interface is then configured. A data source is set up and registered with the
                 * run loop to receive Ethernet packets from the TAP interface.
                 *
                 * The event contains both the source and destination UUIDs, as well as the MTU for this connection and
                 * the BNEP Channel ID, which is used for sending Ethernet packets over BNEP.
                 */
				case BNEP_EVENT_OPEN_CHANNEL_COMPLETE:
                    if (packet[2]) {
                        log_error("BNEP channel open failed, status %02x\n", packet[2]);
                    } else {
                        // data: event(8), len(8), status (8), bnep source uuid (16), bnep destination uuid (16), remote_address (48)
                        uuid_source = READ_BT_16(packet, 3);
                        uuid_dest   = READ_BT_16(packet, 5);
                        mtu         = READ_BT_16(packet, 7);
                        bnep_cid    = channel;
                        //bt_flip_addr(event_addr, &packet[9]);
                        memcpy(&event_addr, &packet[9], sizeof(bd_addr_t));
                        log_error("BNEP connection open succeeded to %s source UUID 0x%04x dest UUID: 0x%04x, max frame size %u\n", bd_addr_to_str(event_addr), uuid_source, uuid_dest, mtu);
                        /* Create the tap interface */
                        hci_local_bd_addr(local_addr);
                        // TODO: open a net I/F like tap_fd = tap_alloc(tap_dev_name, local_addr);
                    }
					break;

                /* @text If there is a timeout during the connection setup, BNEP_EVENT_CHANNEL_TIMEOUT will be received
                 * and the BNEP connection  will be closed
                 */
                case BNEP_EVENT_CHANNEL_TIMEOUT:
                	log_error("BNEP channel timeout! Channel will be closed\n");
                    break;

                /* @text BNEP_EVENT_CHANNEL_CLOSED is received when the connection gets closed.
                 */
                case BNEP_EVENT_CHANNEL_CLOSED:
                	log_error("BNEP channel closed\n");
                    bnep_cid = 0;
                    // TODO: close a net I/F
                	// run_loop_remove_data_source(&tap_dev_ds);
                    break;

                /* @text BNEP_EVENT_READY_TO_SEND indicates that a new packet can be send. This triggers the retry of a
                 * parked network packet. If this succeeds, the data source element is added to the run loop again.
                 */
                case BNEP_EVENT_READY_TO_SEND:
                    // Check for parked network packets and send it out now
                	// TODO: send parked packet
                    break;

                default:
                    break;
            }
            break;

        /* @text Ethernet packets from the remote device are received in the packet handler with type BNEP_DATA_PACKET.
         * It is forwarded to the TAP interface.
         */
        case BNEP_DATA_PACKET:
//        	log_error("recv a packet, size %d bytes", size);
        	bnep_channel_receive_callback(packet, size);
            break;

        default:
            break;
    }
}

// TODO: rename
static int process_tap_dev_data(struct data_source *ds)
{
    if (network_buffer_len > 0 && bnep_cid!=0 && bnep_can_send_packet_now(bnep_cid)) { // FIXME: check channel open?
 //       	log_error("send a packet, size %d bytes", network_buffer_len);
        bnep_send(bnep_cid, network_buffer, network_buffer_len);
        network_buffer_len = 0;  // FIXME: use mutex?
    }
    if (network_buffer_len2 > 0 && bnep_cid!=0 && bnep_can_send_packet_now(bnep_cid)) { // FIXME: check channel open?
//        	log_error("send a packet, size %d bytes", network_buffer_len2);
        bnep_send(bnep_cid, network_buffer2, network_buffer_len2);
        network_buffer_len2 = 0;  // FIXME: use mutex?
    }
    return 0;
}

uint8_t/*FIXME:use bool*/ bnep_channel_send(uint8_t *packet, uint16_t size) {
//        	log_error("LWIP try to send a packet, size %d bytes", size);
    if(size > BNEP_MTU_MIN) {
        log_error("%s(): size too large", __FUNCTION__);
    }
    if (network_buffer_len == 0) {
        memcpy(network_buffer, packet, size);
        network_buffer_len = size; // FIXME: use mutex?
    } else if (network_buffer_len2 == 0) {
        memcpy(network_buffer2, packet, size);
        network_buffer_len2 = size; // FIXME: use mutex?
    } else {
        log_error("%s(): buffer is not empty", __FUNCTION__);
    }
    return 1/*use true*/;
}

static void panu_setup(void){
    // Initialise BNEP
    bnep_init();
    bnep_register_packet_handler(panu_packet_handler);
    // Minimum L2CAP MTU for bnep is 1691 bytes
    bnep_register_service(NULL, SDP_NAP/*SDP_PANU*/, BNEP_MTU_MIN);
    // Register SDP
    static uint8_t panu_sdp_record[256];
    service_record_item_t * service_record_item = (service_record_item_t *) panu_sdp_record;
#define NETWORK_TYPE_IPv4       0x0800
#define NETWORK_TYPE_ARP        0x0806
    uint16_t network_packet_types[] = { NETWORK_TYPE_IPv4, NETWORK_TYPE_ARP, 0};    // 0 as end of list
    //pan_create_panu_service((uint8_t*) &service_record_item->service_record, network_packet_types, NULL, NULL, BNEP_SECURITY_NONE);
    pan_create_nap_service((uint8_t*) &service_record_item->service_record, network_packet_types, NULL, NULL, BNEP_SECURITY_NONE, PAN_NET_ACCESS_TYPE_NONE, 0, NULL, NULL);
    sdp_register_service_internal(NULL, service_record_item);

    // Add data source to send packets
    static data_source_t tap_dev_ds;
    tap_dev_ds.fd = 0;
    tap_dev_ds.process = process_tap_dev_data;
    run_loop_add_data_source(&tap_dev_ds);

}
