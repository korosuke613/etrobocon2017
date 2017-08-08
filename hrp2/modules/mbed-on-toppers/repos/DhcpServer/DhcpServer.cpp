#include "mbed.h"
#include "rtos.h"
#include "lwip/netif.h"
#include "UDPSocket.h"
#include "SocketAddress.h"
#include "lwip/dhcp.h"
#include "lwip/api.h"
#include "DhcpServer.h"
#include "lwip_stack.h"

//For debug -- ertl-liyixiao
#if 0
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#endif

#define CONNECT_NUM    (5)
#define IP_ADDER_START (10)

#define OFS_XID        (4)
#define OFS_YIADDR     (16)
#define OFS_SIADDR     (20)
#define OFS_CHADDR     (28)
#define OFS_SNAME      (44)
#define OFS_COOKIE     (236)
#define OFS_OPTIONS    (240)

static char receivebuff[500];
static char sendbuff[300] = {0};
//static UDPSocket dhcp_server; // FIXME: global cons is not supported!
static Thread * dhcpThread = NULL;
static char chaddr_tbl[CONNECT_NUM][6] = {0};
static const char mac_no_use[6] = {0, 0, 0, 0, 0, 0};

/**
 * UDPSocket supports broadcasting, only lwIP is supported.
 * Extending nsapi_option_t seems good, but I don't want to modify code in mbed-os.
 * -- ertl-liyixiao
 */
class LwipUDPSocket : public UDPSocket {
    // FIXME: must keep consistency with 'lwip_stack.c'
    struct lwip_socket {
        bool in_use;

        struct netconn *conn;
        struct netbuf *buf;
        u16_t offset;

        void (*cb)(void *);
        void *data;
    };
public:
    LwipUDPSocket() : UDPSocket(&lwip_stack) {
        struct lwip_socket *s = (struct lwip_socket *)_socket;
        s->conn->pcb.ip->so_options |= SOF_BROADCAST;
    }
    virtual ~LwipUDPSocket() {}
};

static void dhcp_task_static(void const *argument) {
    static LwipUDPSocket dhcp_server;
    static const SocketAddress client("255.255.255.255", 68);

    int cnt;
    int tbl_index;

    dhcp_server.bind(67);

    while (true) {
        int n = dhcp_server.recvfrom(NULL, receivebuff, sizeof(receivebuff));
        if (n > 0) {

            sendbuff[OFS_XID + 0]    = receivebuff[OFS_XID + 0];
            sendbuff[OFS_XID + 1]    = receivebuff[OFS_XID + 1];
            sendbuff[OFS_XID + 2]    = receivebuff[OFS_XID + 2];
            sendbuff[OFS_XID + 3]    = receivebuff[OFS_XID + 3];

            tbl_index = -1;
            for (cnt = 0; cnt < CONNECT_NUM; cnt++) {
                if (memcmp(&receivebuff[OFS_CHADDR], chaddr_tbl[cnt], 6) == 0) {
                    tbl_index = cnt;
                    break;
                }
            }
            if (tbl_index == -1) {
                sendbuff[OFS_YIADDR + 0] = 0;
                sendbuff[OFS_YIADDR + 1] = 0;
                sendbuff[OFS_YIADDR + 2] = 0;
                sendbuff[OFS_YIADDR + 3] = 0;
            } else {
                sendbuff[OFS_YIADDR + 0] = sendbuff[OFS_SIADDR + 0];
                sendbuff[OFS_YIADDR + 1] = sendbuff[OFS_SIADDR + 1];
                sendbuff[OFS_YIADDR + 2] = sendbuff[OFS_SIADDR + 2];
                sendbuff[OFS_YIADDR + 3] = IP_ADDER_START + tbl_index;
            }

            sendbuff[OFS_CHADDR + 0] = receivebuff[OFS_CHADDR + 0];
            sendbuff[OFS_CHADDR + 1] = receivebuff[OFS_CHADDR + 1];
            sendbuff[OFS_CHADDR + 2] = receivebuff[OFS_CHADDR + 2];
            sendbuff[OFS_CHADDR + 3] = receivebuff[OFS_CHADDR + 3];
            sendbuff[OFS_CHADDR + 4] = receivebuff[OFS_CHADDR + 4];
            sendbuff[OFS_CHADDR + 5] = receivebuff[OFS_CHADDR + 5];

            if (receivebuff[OFS_OPTIONS + 2] == DHCP_DISCOVER) {
                sendbuff[OFS_OPTIONS + 2]  = DHCP_OFFER;
                if (tbl_index == -1) {
                    for (cnt = 0; cnt < CONNECT_NUM; cnt++) {
                        if (memcmp( chaddr_tbl[cnt], mac_no_use, 6) == 0) {
                            tbl_index = cnt;
                            break;
                        }
                    }
                }
                if (tbl_index != -1) {
                    chaddr_tbl[tbl_index][0]  = receivebuff[OFS_CHADDR + 0];
                    chaddr_tbl[tbl_index][1]  = receivebuff[OFS_CHADDR + 1];
                    chaddr_tbl[tbl_index][2]  = receivebuff[OFS_CHADDR + 2];
                    chaddr_tbl[tbl_index][3]  = receivebuff[OFS_CHADDR + 3];
                    chaddr_tbl[tbl_index][4]  = receivebuff[OFS_CHADDR + 4];
                    chaddr_tbl[tbl_index][5]  = receivebuff[OFS_CHADDR + 5];
                    sendbuff[OFS_YIADDR + 0] = sendbuff[OFS_SIADDR + 0];
                    sendbuff[OFS_YIADDR + 1] = sendbuff[OFS_SIADDR + 1];
                    sendbuff[OFS_YIADDR + 2] = sendbuff[OFS_SIADDR + 2];
                    sendbuff[OFS_YIADDR + 3] = IP_ADDER_START + tbl_index;
                }
                dhcp_server.sendto(client, sendbuff, 300);
            } else if (receivebuff[OFS_OPTIONS + 2] == DHCP_REQUEST) {
                if (tbl_index != -1) {
                    sendbuff[OFS_OPTIONS + 2]  = DHCP_ACK;
                } else {
                    sendbuff[OFS_OPTIONS + 2]  = DHCP_NAK;
                }
                dhcp_server.sendto(client, sendbuff, 300);
            } else if (receivebuff[OFS_OPTIONS + 2] == DHCP_RELEASE) {
                if (tbl_index != -1) {
                    memset(chaddr_tbl[tbl_index], 0, 6);
                }
            } else {
                // do nothing
            }
        }
    }
}

DhcpServer::DhcpServer(char * name, char * ipadder) {
    int i;
    int len;
    int ofs;

#if 1 // original code will cause data abort (or unaligned) on some targets -- ertl-liyixiao
    uint32_t ipsub[4];
    sscanf(ipadder, "%d.%d.%d.%d", ipsub+0, ipsub+1, ipsub+2, ipsub+3);
    sendbuff[OFS_SIADDR+0]=ipsub[0];
    sendbuff[OFS_SIADDR+1]=ipsub[1];
    sendbuff[OFS_SIADDR+2]=ipsub[2];
    sendbuff[OFS_SIADDR+3]=ipsub[3];
#else
    sscanf(ipadder, "%d.%d.%d.%d", (int *)&sendbuff[OFS_SIADDR + 0], (int *)&sendbuff[OFS_SIADDR + 1],
    (int *)&sendbuff[OFS_SIADDR + 2], (int *)&sendbuff[OFS_SIADDR + 3]);
#endif

    len = strlen(name);
    for (i = 0; (i < len) && (i < DHCP_SNAME_LEN); i++) {
        sendbuff[OFS_SNAME + i] = name[i];
    }

    sendbuff[0] = 0x02;
    sendbuff[1] = 0x01;
    sendbuff[2] = 0x06;
    sendbuff[3] = 0x00;

    sendbuff[OFS_COOKIE + 0] = 0x63;
    sendbuff[OFS_COOKIE + 1] = 0x82;
    sendbuff[OFS_COOKIE + 2] = 0x53;
    sendbuff[OFS_COOKIE + 3] = 0x63;

    ofs = OFS_OPTIONS;
    sendbuff[ofs++] = DHCP_OPTION_MESSAGE_TYPE;
    sendbuff[ofs++] = DHCP_OPTION_MESSAGE_TYPE_LEN;
    sendbuff[ofs++] = 0;

    sendbuff[ofs++] = DHCP_OPTION_SERVER_ID;
    sendbuff[ofs++] = 0x04;
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 0];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 1];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 2];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 3];

    sendbuff[ofs++] = DHCP_OPTION_LEASE_TIME;
    sendbuff[ofs++] = 0x04;
    sendbuff[ofs++] = 0x00;
    sendbuff[ofs++] = 0x01;
    sendbuff[ofs++] = 0x4e;
    sendbuff[ofs++] = 0x20;

    sendbuff[ofs++] = DHCP_OPTION_SUBNET_MASK;
    sendbuff[ofs++] = 0x04;
    sendbuff[ofs++] = 0xff;
    sendbuff[ofs++] = 0xff;
    sendbuff[ofs++] = 0xff;
    sendbuff[ofs++] = 0xf0;

    sendbuff[ofs++] = DHCP_OPTION_ROUTER;
    sendbuff[ofs++] = 0x04;
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 0];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 1];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 2];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 3];

    sendbuff[ofs++] = DHCP_OPTION_DNS_SERVER;
    sendbuff[ofs++] = 0x04;
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 0];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 1];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 2];
    sendbuff[ofs++] = sendbuff[OFS_SIADDR + 3];

    sendbuff[ofs++] = 0xff;

    if (dhcpThread == NULL) {
        dhcpThread = new Thread(&dhcp_task_static, NULL, osPriorityNormal, (1024 * 8));
    }
}

DhcpServer::~DhcpServer() {
    if (dhcpThread != NULL) {
        delete dhcpThread;
    }
}
