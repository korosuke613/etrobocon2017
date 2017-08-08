#include "EthernetInterface.h"
#include "DhcpServer.h"
#include "lwip/apps/httpd.h"

osMutexId httpd_post_mutex_id;

extern "C"
void toppers_mbed_start_lwip(const char *ipv4addr) {
    httpd_post_mutex_id = osMutexCreate(NULL);
    assert(httpd_post_mutex_id > 0);
//    debug("connect eth.\r\n");
    auto eth = new EthernetInterface();
    eth->set_network(ipv4addr, "255.255.255.0", ipv4addr);
    eth->connect();
//    debug("start dhcp\r\n");
    auto dhcp_server = new DhcpServer("HostName", ipv4addr/*eth->get_ip_address()*/);
    httpd_init();
}

// FIXME: this is a workaround for compiler
void *__dso_handle=0;
