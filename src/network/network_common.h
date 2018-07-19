/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
#pragma once

#include "lwm2m/c_connect.h"
#include "lwm2m/network.h"
#include "wakaama_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(LWIP) && defined(POSIX_NETWORK)
#error "You cannot define LWIP and POSIX_NETWORK!"
#endif

#if !defined(LWIP) && !defined(POSIX_NETWORK)
    #if defined(_WIN32) || defined(__unix__) || defined(__posix__) || defined(__linux) || defined(linux)
    #define POSIX_NETWORK 1
    #else
    #error "Must be LWIP or POSIX_NETWORK"
    #endif
#endif

#ifdef LWM2M_WITH_DTLS
#include "mbedtls/ssl.h"
#include "mbedtls/ssl_cookie.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"
#endif

#ifdef POSIX_NETWORK
#include "network_posix.h"
    #ifdef _WIN32
        #include "wepoll/wepoll.h"
    #else
        #include <sys/epoll.h>
    #endif
#endif

#ifdef LWIP
#include "network_lwip.h"
#endif

#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct _network_t_ network_t;

// Connection structures form a linked list and consist of
// an identifier (socket number), and the destination address,
// as well as the ssl/dtls connection context.
typedef struct _connection_t
{
    struct _connection_t *  next;
    network_t* network;
    uint16_t shortServerID;  ///< The lwm2m short server id. Is always 0 on a lwm2m server.
    addr_t addr;             ///< The IP address/port of this connection
    sock_t* sock;            ///< Connection socket reference
    #ifdef LWM2M_WITH_DTLS
    mbedtls_ssl_context ssl; ///< Connection ssl context
    mbedtls_ssl_config conf; ///< Connection ssl configuration
    bool dtls;               ///< Is this a dtls connection?
    uint32_t tmr_intermediate_ms;
    uint32_t tmr_final_ms;   ///< A timer is active if this is != 0
    time_t tmr_current;
    #endif
    #ifdef LWIP
    struct pbuf *p;          ///< Receive buffer
    #endif
} connection_t;

typedef enum {
    NET_CLIENT_PROCESS,
    NET_SERVER_PROCESS
} network_process_type_t;

#ifndef LWM2M_MAX_SOCKETS
#define LWM2M_MAX_SOCKETS 10
#endif

// This structure is stored in the wakama context custom object
// and consists of all open/bound network sockets, network interfaces,
// and dtls common stuff like entropy and random generator.
typedef struct _network_t_ {
    time_t due_time_ms; // due time in milliseconds
    connection_t* connection_list;
    network_process_type_t type;
    #ifdef LWM2M_WITH_DTLS
    enum DtlsHandshakeState handshakeState;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    #endif
    // In server mode with enabled DTLS, we need the preshared information
    #if defined(LWM2M_WITH_DTLS) && defined(LWM2M_SERVER_MODE)
    char *                       publicIdentity;
    uint16_t                     publicIdLen;
    char *                       serverPublicKey;
    uint16_t                     serverPublicKeyLen;
    char *                       secretKey;
    uint16_t                     secretKeyLen;
    #ifdef LWM2M_WITH_DTLS_CERTIFICATES
    mbedtls_x509_crt             certs;
    mbedtls_pk_context           pkey;
    #endif
    #ifdef MBEDTLS_SSL_DTLS_HELLO_VERIFY
    mbedtls_ssl_cookie_ctx cookies;
    #endif
    #endif
    #ifdef POSIX_NETWORK
    int epfd; // epoll descriptor
    #endif
    unsigned open_listen_sockets;
    sock_t socket_handle[LWM2M_MAX_SOCKETS]; // Array of socket handles
} network_t;

// Parse uri in the form "coap[s]://[host]:[port]". host can be an IPv6 address ( "[::]" ).
// The original c-string is modified and host and port will
// contain a reference to the respective part of the uri c-string.
// Return 1 on success and non-secured, 2 on success for a secured host and 0 otherwise.
uint8_t decode_uri(char* uri, char** host, uint16_t *port);

void internal_network_add_conn(network_t* network, connection_t* conn);
connection_t * internal_connection_find(network_t * network, addr_t addr);
connection_t * internal_connection_create(network_t * network, char * host, uint16_t port);
uint8_t internal_init_sockets(lwm2m_context_t *contextP, network_t* network, uint16_t localPort);
void internal_closeSocket(network_t* network, unsigned socket_handle);
void internal_network_read(lwm2m_context_t* contextP, void* dest, size_t len, connection_t* connection);
void internal_network_close(network_t* network);

bool ip_equal(addr_t a, addr_t b);

#ifdef LWM2M_NETWORK_LOGGING
void connection_log_io(connection_t* conn, int length, bool sending);
#define network_log_info(...) fprintf(stderr, __VA_ARGS__)
#define network_log_error(...) fprintf(stderr, __VA_ARGS__)
#else
#define connection_log_io(...) {}
#define network_log_info(...)
#define network_log_error(...)
#endif

#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE 1024
#endif

int mbedtls_net_send( void *ctx, const unsigned char *buf, size_t len );
int mbedtls_net_recv( void *ctx, unsigned char *buf, size_t len );

inline static network_t* network_from_context(lwm2m_context_t* contextP) { return (network_t*)contextP->userData; }

/**
 * `lwm2m_process` need to be called periodically and will provide an internal value in seconds when the next call is due.
 * This function returns a pointer to this due time value. You can modify (decrease) the value if required (`lwm2m_watch_and_reconnect`
 * and the ssl handshake code are doing this for example). This will cause `lwm2m_block_wait` to return sooner than the given timeout.
 *
 * @param contextP Wakaama context
 * @return A pointer to the next due time in milliseconds
 */
inline static time_t* lwm2m_due_time(lwm2m_context_t * contextP) { return &network_from_context(contextP)->due_time_ms; }

/// Internal SSL methods
int init_server_connection_ssl(connection_t* connection, network_t* network);
bool internal_network_ssl_init(network_t* network);
void internal_check_timer(lwm2m_context_t *contextP);
connection_t * internal_configure_ssl(connection_t * connection, network_t *network, security_instance_t *secInst);
void internal_close_connection_ssl(network_t* network, connection_t * t);
void internal_network_close_ssl(network_t* network);

#ifdef LWM2M_SERVER_MODE
connection_t* internal_create_server_connection(network_t* network, addr_t addr);
#endif

#ifdef __cplusplus
}
#endif
