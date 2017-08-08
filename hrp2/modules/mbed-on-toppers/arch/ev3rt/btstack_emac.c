#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"
#include "lwip/ethip6.h"
#include "mbed_interface.h"

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <string.h>
#include "btstack-interface.h"

static struct netif *netif = NULL;

void bnep_channel_receive_callback(uint8_t *packet, uint16_t size) {
    // TODO: is zero copy possible?
    if (netif == NULL) {
        assert(false);  // FIXME: handle this
        return;
    }

//    SYSUTM utm1, utm2;
//    get_utm(&utm1);

    struct pbuf *p = pbuf_alloc(PBUF_RAW, size, PBUF_RAM);
    memcpy(p->payload, packet, size);
    p->len = size;
    /* full packet send to tcpip_thread to process */
    if (netif->input(p, netif) != ERR_OK) {
        /* Free buffer */
        pbuf_free(p);
        assert(false); // FIXME: handle this
    }
//    get_utm(&utm2);
//    syslog(LOG_ERROR, "%s costs %d us", __FUNCTION__, utm2 - utm1);
}

static err_t btstack_linkoutput(struct netif *netif, struct pbuf *p) {
    struct pbuf *q;
    s32_t       cnt;
    err_t       err        = ERR_MEM;
    s32_t       write_size = 0;

    static char buf[4096]; // FIXME: zero copy
    int len = 0;

    if ((p->payload != NULL) && (p->len != 0)) {
        for (q = p; q != NULL; q = q->next) {
            memcpy(buf + len, q->payload, q->len);
            len += q->len;
        }
            if (!bnep_channel_send(buf, len)) {
                assert(false); // FIXME: handle this
            } else
        err = ERR_OK;
    }

    return err;
}

err_t eth_arch_enetif_init(struct netif *_netif)
{
    netif = _netif;

    /* set MAC hardware address */
#if (MBED_MAC_ADDRESS_SUM != MBED_MAC_ADDR_INTERFACE)
    netif->hwaddr[0] = MBED_MAC_ADDR_0;
    netif->hwaddr[1] = MBED_MAC_ADDR_1;
    netif->hwaddr[2] = MBED_MAC_ADDR_2;
    netif->hwaddr[3] = MBED_MAC_ADDR_3;
    netif->hwaddr[4] = MBED_MAC_ADDR_4;
    netif->hwaddr[5] = MBED_MAC_ADDR_5;
#else
    mbed_mac_address((char *)netif->hwaddr);
#endif
    netif->hwaddr_len = ETH_HWADDR_LEN;

    /* maximum transfer unit */
    netif->mtu = 1500; // FIXME: check this

    /* device capabilities */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET;
#ifdef LWIP_IGMP
    netif->flags |= NETIF_FLAG_IGMP;
#endif
#if LWIP_IPV6_MLD
    netif->flags |= NETIF_FLAG_MLD6;
#endif

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "lwiprza1";
#endif /* LWIP_NETIF_HOSTNAME */

    netif->name[0] = 'e';
    netif->name[1] = 'n';

#if LWIP_IPV4
    netif->output = etharp_output; // FIXME: check IF status like rza1_etharp_output_ipv4?
#endif
#if LWIP_IPV6
  netif->output_ip6 = rza1_etharp_output_ipv6;
#endif

    netif->linkoutput = btstack_linkoutput;

    netif_set_link_up(netif);

    return ERR_OK;
}

void eth_arch_enable_interrupts(void) {
    // FIXME: support this
    // ethernetext_start_stop(1);
}

void eth_arch_disable_interrupts(void) {
    // ethernetext_start_stop(0);
}
