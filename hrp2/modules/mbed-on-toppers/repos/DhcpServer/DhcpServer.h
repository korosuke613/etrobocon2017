/**************************************************************************//**
* @file          DhcpServer.h
* @brief         DhcpServer API
******************************************************************************/
#ifndef DHCP_SERVER_H_
#define DHCP_SERVER_H_

/** This class is intended for use the mbed board as a DHCP server.
 *  This class can be allocated five IP addresses.
 *  Top 3byte of IP address is the same as the server address, the lower 1byte is 10-14 is allocated.
 *  For example, if the server address is "192.168.0.1", IP address will be allocated "192.168.0.10" ~ "192.168.0.14".
 */
class DhcpServer {
public:
    /** Constructor: Initializes DhcpServer.
     *
     * @param name a pointer to a string containing the server name. (e.g."ServerName")
     * @param ipadder a pointer to a string containing the server IP address. (e.g."192.168.0.1")
     */
    DhcpServer(char * name, char * ipadder);

    /** Destructor
     *
     */
    virtual ~DhcpServer();
};
#endif /* DHCP_SERVER_H_ */
