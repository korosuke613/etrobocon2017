#pragma once

/**
 * Provided interface
 */

void toppers_mbed_initialize(); // Must be called once before using toppers_mbed_start_xxx functions

void toppers_mbed_start_lwip(const char *ipv4addr); // Start lwIP and DHCP server with a static IP address

void httpd_receive_file_start(void *buffer, uint32_t size); // Start to receive a file over HTTP, any HTTP request before this call will be dropped. (buffer=NULL means cancel & disable)
int  http_receive_file_poll(const char **filename, uint32_t *size); // File name ("" means a firmware i.e. uImage received) and size will be filled if a file has been received. Return 0 means not yet.

/**
 * Required interface
 */

