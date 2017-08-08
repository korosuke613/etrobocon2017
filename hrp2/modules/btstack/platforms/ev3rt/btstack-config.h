#ifndef __BTSTACK_CONFIG
#define __BTSTACK_CONFIG

#include <stdint.h>
#include "btstack-interface.h"

#define EMBEDDED

// #define HAVE_INIT_SCRIPT
// #define HAVE_EHCILL

// #define HAVE_BZERO
#define HAVE_TICK

// #define HAVE_BLE

// #define HAVE_HCI_DUMP
#define hci_dump_packet(...)
// #define ENABLE_LOG_INFO 
#define ENABLE_LOG_ERROR

// Use syslog instead of printf
void syslog(unsigned int prio, const char *format, ...);
#define BTSTACK_PRINTF(format, ...) syslog(3U/*LOG_ERROR*/, format, ## __VA_ARGS__)

#define HCI_ACL_PAYLOAD_SIZE (1691+4)

#define MAX_SPP_CONNECTIONS 1
#define MAX_NO_BNEP_SERVICES 1
#define MAX_NO_BNEP_CHANNELS 1
#define MAX_NO_HCI_CONNECTIONS MAX_SPP_CONNECTIONS
#define MAX_NO_L2CAP_SERVICES  (2+MAX_NO_BNEP_SERVICES)
#define MAX_NO_L2CAP_CHANNELS  (1+MAX_SPP_CONNECTIONS+MAX_NO_BNEP_CHANNELS)
#define MAX_NO_RFCOMM_MULTIPLEXERS MAX_SPP_CONNECTIONS
#define MAX_NO_RFCOMM_SERVICES 1
#define MAX_NO_RFCOMM_CHANNELS MAX_SPP_CONNECTIONS
#define MAX_NO_DB_MEM_DEVICE_LINK_KEYS  2
#define MAX_NO_DB_MEM_DEVICE_NAMES 0
#define MAX_NO_DB_MEM_SERVICES 1
#define MAX_NO_HFP_CONNECTIONS 0

#endif
