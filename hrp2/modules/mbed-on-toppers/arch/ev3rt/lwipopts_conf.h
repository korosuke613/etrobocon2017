/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LWIPOPTS_CONF_H
#define LWIPOPTS_CONF_H

#define LWIP_TRANSPORT_ETHERNET       1

#define MEM_SIZE                      (1600 * 16)
#define TCPIP_THREAD_STACKSIZE (4096)
#define TCP_MSS (1460)
#define TCP_WND (8192)

/**
 * FIXME: It seems memp implementation is buggy
 * when using httpd so we define this flag. -- ertl-liyixiao
 */
#define MEMP_MEM_MALLOC 1

#define LWIP_HTTPD_SUPPORT_POST 1

// TODO: this should be generated from 'mbed-lib.json'
#define MBED_CONF_LWIP_IPV4_ENABLED 1
#define MBED_CONF_LWIP_IPV6_ENABLED 0
#define MBED_CONF_LWIP_IP_VER_PREF  4
#define MBED_CONF_LWIP_ADDR_TIMEOUT 5

#define LWIP_DEBUG
//#define HTTPD_DEBUG LWIP_DBG_ON

#endif
