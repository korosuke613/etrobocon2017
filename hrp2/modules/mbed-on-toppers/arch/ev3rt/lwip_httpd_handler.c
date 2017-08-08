 /*
 * lwip_httpd_handler.c
 *
 *  Created on: Nov 10, 2016
 *      Author: liyixiao
 */

#define _GNU_SOURCE // for memmem
#include "lwip/apps/httpd.h"
#include "string.h"

/**
 * mbed interface for EV3RT
 */

extern osMutexId httpd_post_mutex_id;

static void    *current_connection  = NULL;
static uint8_t *current_write_pointer; 
static int      current_content_length;
static char     file_name[1024];
static uint32_t file_size;
static bool_t   file_is_received = false;
#define post_data_len (current_write_pointer - post_buffer)

static uint8_t *post_buffer      = NULL;
static uint32_t post_buffer_size;

void httpd_receive_file_start(void *buffer, uint32_t size) {
    osMutexWait(httpd_post_mutex_id, osWaitForever);
    current_connection = NULL; // drop all previous requests
    post_buffer = buffer;
    post_buffer_size = size;
    file_is_received = false;
    osMutexRelease(httpd_post_mutex_id);
}

int http_receive_file_poll(const char **filename, uint32_t *size) {
    int res = false;
    osMutexWait(httpd_post_mutex_id, osWaitForever);
    if (file_is_received) {
        *filename = file_name;
        *size     = file_size;
        res = true;
    }
    osMutexRelease(httpd_post_mutex_id);
    return res;
}

// ============================= Handle HTTP POST Requests =============================

#define EV3RT_UPLOAD_URI  "/upload"
#define HEADER_TYPE_APP   "\r\nContent-Type: ev3rt/app\r\n"
#define HEADER_TYPE_IMG   "\r\nContent-Type: ev3rt/img\r\n"
#define HEADER_FILENAME   "\r\nContent-Disposition: inline; filename=\""

/** Called when a POST request has been received. The application can decide
 * whether to accept it or not.
 *
 * @param connection Unique connection identifier, valid until httpd_post_end
 *        is called.
 * @param uri The HTTP header URI receiving the POST request.
 * @param http_request The raw HTTP request (the first packet, normally).
 * @param http_request_len Size of 'http_request'.
 * @param content_len Content-Length from HTTP header.
 * @param response_uri Filename of response file, to be filled when denying the
 *        request
 * @param response_uri_len Size of the 'response_uri' buffer.
 * @param post_auto_wnd Set this to 0 to let the callback code handle window
 *        updates by calling 'httpd_post_data_recved' (to throttle rx speed)
 *        default is 1 (httpd handles window updates automatically)
 * @return ERR_OK: Accept the POST request, data may be passed in
 *         another err_t: Deny the POST request, send back 'bad request'.
 */
err_t httpd_post_begin(void *connection, const char *uri, const char *http_request,
                       u16_t http_request_len, int content_len, char *response_uri,
                       u16_t response_uri_len, u8_t *post_auto_wnd) {
    const char *this_filename_buf = NULL;
    int this_filename_len = 0;

    if (strcmp(EV3RT_UPLOAD_URI, uri) != 0) {  // Only upload is supported
        syslog(LOG_ERROR, "HTTP POST URI is invalid.");
        return ERR_ARG;
    }
    if (memmem(http_request, http_request_len, HEADER_TYPE_APP, strlen(HEADER_TYPE_APP))) { // Receive an application
        if ((this_filename_buf = memmem(http_request, http_request_len, HEADER_FILENAME, strlen(HEADER_FILENAME))) != NULL) {
            // TODO: check file name more carefully
            this_filename_buf += strlen(HEADER_FILENAME);
            const char *filename_end = memmem(this_filename_buf, http_request_len - (this_filename_buf - http_request), "\"\r\n", strlen("\"\r\n"));
            assert(filename_end);
            this_filename_len = filename_end - this_filename_buf;
        }
        if (this_filename_buf == NULL || this_filename_len == 0 || this_filename_len >= sizeof(file_name)) {
            syslog(LOG_ERROR, "HTTP POST file name is invalid.");
            return ERR_ARG;
        }
    } else if (memmem(http_request, http_request_len, HEADER_TYPE_IMG, strlen(HEADER_TYPE_IMG))) { // Receive an image
        this_filename_len = 0;
    } else {
        syslog(LOG_ERROR, "HTTP POST Content-Type is invalid.");
        return ERR_ARG;
    }

    err_t res = ERR_OK;

    osMutexWait(httpd_post_mutex_id, osWaitForever);
    if (post_buffer) {
        assert(http_request_len + content_len <= post_buffer_size);
        current_connection = connection;
        current_write_pointer = post_buffer;
        assert(this_filename_len < sizeof(file_name));
        memcpy(file_name, this_filename_buf, this_filename_len);
        file_name[this_filename_len] = '\0';
        file_size = content_len;
        file_is_received = false;
        memcpy(current_write_pointer, http_request, http_request_len);
        current_write_pointer += http_request_len;
    } else res = ERR_ARG;
    osMutexRelease(httpd_post_mutex_id);
    return res;
    //return ERR_ARG;
}

/** Called for each pbuf of data that has been received for a POST.
 * ATTENTION: The application is responsible for freeing the pbufs passed in!
 *
 * @param connection Unique connection identifier.
 * @param p Received data.
 * @return ERR_OK: Data accepted.
 *         another err_t: Data denied, http_post_get_response_uri will be called.
 */
err_t httpd_post_receive_data(void *connection, struct pbuf *p) {
    err_t res = ERR_OK;
    osMutexWait(httpd_post_mutex_id, osWaitForever);
    if (current_connection == connection) {
        memcpy(current_write_pointer, p->payload, p->len);
        current_write_pointer += p->len;
        pbuf_free(p);
    } else return ERR_ARG;
    osMutexRelease(httpd_post_mutex_id);
    return res;
}

/** Called when all data is received or when the connection is closed.
 * The application must return the filename/URI of a file to send in response
 * to this POST request. If the response_uri buffer is untouched, a 404
 * response is returned.
 *
 * @param connection Unique connection identifier.
 * @param response_uri Filename of response file, to be filled when denying the request
 * @param response_uri_len Size of the 'response_uri' buffer.
 */
void httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len) {
    osMutexWait(httpd_post_mutex_id, osWaitForever);
    syslog(LOG_NOTICE, "Recv POST finished, total %d bytes received, name '%s', filesz %d bytes.", post_data_len, file_name, file_size);
    if (current_connection == connection && post_data_len >= file_size + 4) {
        assert(memcmp("\0\n\r\n", current_write_pointer - file_size - 4, 4) == 0); /* seems lwIP will trim http header */
        memmove(post_buffer, current_write_pointer - file_size, file_size);
        post_buffer = NULL, current_connection = NULL; // drop all post requests
        response_uri[0] = '/', response_uri[1] = '\0';
        file_is_received = true;
    }
    osMutexRelease(httpd_post_mutex_id);
}
