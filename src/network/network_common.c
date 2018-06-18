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

#include "lwm2m/network.h"
#include "lwm2m/connect.h"
#include "lwm2m/debug.h"
#include "../internal.h"
#include "network_common.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

uint8_t decode_uri(char* uri, char** host, char** port)
{
    uint8_t r=0;
    // parse uri in the form "coaps://[host]:[port]"
    if (0 == strncmp(uri, "coaps://", sizeof("coaps://")-1))
    {
        *host = uri+sizeof("coaps://")-1;
        r=2;
    }
    else if (0 == strncmp(uri, "coap://", sizeof("coap://")-1))
    {
        *host = uri+sizeof("coap://")-1;
        r=1;
    }
    else
    {
        return r;
    }
    char* afterHost = strrchr(*host, ':');
    *port = afterHost;
    if (*port == NULL) {
        *port = r==1?LWM2M_DEFAULT_SERVER_PORT:LWM2M_DEFAULT_SECURE_SERVER_PORT;
        afterHost = *host + strlen(*host);
    } else {
        // split strings
        **port = 0;
        (*port)++;

    }

    // remove brackets if ipv6 addresses
    if (*host[0] == '[')
    {
        *host = *host + 1;
        if (*(afterHost - 1) == ']')
        {
            *(afterHost - 1) = 0;
        }
        else
            return 0;
    }
    return r;
}


#ifndef timercmp
# define timercmp(a, b, CMP) 						      \
  (((a)->tv_sec == (b)->tv_sec) ? 					      \
   ((a)->tv_usec CMP (b)->tv_usec) : 					      \
   ((a)->tv_sec CMP (b)->tv_sec))
#endif

#ifdef LWM2M_WITH_DTLS
/**
 * \brief          Set a pair of delays to watch
 *                 (See \c mbedtls_timing_get_delay().)
 *
 * \param data     Pointer to timing data.
 *                 Must point to a valid \c mbedtls_timing_delay_context struct.
 * \param int_ms   First (intermediate) delay in milliseconds.
 *                 The effect if int_ms > fin_ms is unspecified.
 * \param fin_ms   Second (final) delay in milliseconds.
 *                 Pass 0 to cancel the current delay.
 *
 * \note           To set a single delay, either use \c mbedtls_timing_set_timer
 *                 directly or use this function with int_ms == fin_ms.
 */
static void set_delay( void *data, uint32_t int_ms, uint32_t fin_ms ) {
    connection_t * connection = (connection_t *)data;
    connection->tmr_intermediate_ms = int_ms;
    connection->tmr_final_ms = fin_ms;
    gettimeofday( &connection->tmr_current, NULL );

    if (!fin_ms) {
        connection->network->cached_next_timer_connection = NULL;
        return;
    }

    connection_t * next_timer_connection = connection->network->cached_next_timer_connection;

    // cached_next_timer_connection always points to the next point in time of all connections
    if (next_timer_connection) {
        if (next_timer_connection == connection) return;
        if (timercmp(&next_timer_connection->tmr_current,&connection->tmr_current,>)) {
            connection->network->cached_next_timer_connection = connection;
        }
    } else
        connection->network->cached_next_timer_connection = connection;
}

/**
 * \brief          Get the status of delays
 *                 (Memory helper: number of delays passed.)
 *
 * \param data     Pointer to timing data
 *                 Must point to a valid \c mbedtls_timing_delay_context struct.
 *
 * \return         -1 if cancelled (fin_ms = 0),
 *                  0 if none of the delays are passed,
 *                  1 if only the intermediate delay is passed,
 *                  2 if the final delay is passed.
 */
static int get_delay( void *data ){
    connection_t * connection = (connection_t *)data;

    unsigned long elapsed_ms;

    if( connection->tmr_final_ms == 0 )
        return( -1 );

    struct timeval now;
    gettimeofday( &now, NULL );
    elapsed_ms = (unsigned long)( now.tv_sec  - connection->tmr_current.tv_sec  ) * 1000ul
          + (unsigned long)( now.tv_usec - connection->tmr_current.tv_usec ) / 1000;

    if( elapsed_ms >= connection->tmr_final_ms )
        return( 2 );

    if( elapsed_ms >= connection->tmr_intermediate_ms )
        return( 1 );

    return( 0 );
}
#endif

intptr_t lwm2m_network_native_sock(lwm2m_context_t * contextP, uint8_t sock_no) {
    network_t* network = (network_t*)contextP->userData;
    if (!network) return -1;
    return (intptr_t)network->socket_handle[sock_no];
}

void lwm2m_network_force_interface(lwm2m_context_t * contextP, void* interface)
{
    network_t* network = (network_t*)contextP->userData;
    connection_t * connP = (connection_t*)network->connection_list;
    while (connP != NULL) {
        connP->addr.net_if_out = interface;
        connP = (connection_t*)connP->next;
    }
}

bool lwm2m_session_is_equal(void * session1,
                            void * session2,
                            void * userData)
{
    (void)userData;
    return (session1 == session2);
}

#ifdef LWM2M_WITH_DTLS
static void my_debug( void *ctx, int level,
                      const char *file, int line, const char *str )
{
    (void) ctx;
    (void) level;
    network_log_error("%s:%04d: %s", file, line, str);
}
#endif


#ifdef LWM2M_SERVER_MODE

#ifdef LWM2M_WITH_DTLS
static int cb_check_psk(void *parameter, mbedtls_ssl_context *ssl, const unsigned char *psk_identity, size_t identity_len) {
    network_t* network = (network_t*)parameter;
    (void)psk_identity;
    (void)identity_len;
    return mbedtls_ssl_set_hs_psk(ssl,(const unsigned char*)network->secretKey,network->secretKeyLen);
}

static inline int init_server_connection_ssl(connection_t* connection, network_t* network) {
    int ret;
    mbedtls_ssl_init( &connection->ssl );
    mbedtls_ssl_config_init( &connection->conf );
    if( ( ret = mbedtls_ssl_config_defaults( &connection->conf,
                    MBEDTLS_SSL_IS_SERVER,
                    MBEDTLS_SSL_TRANSPORT_DATAGRAM,
                    MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
    {
        network_log_error("mbedtls_ssl_config_defaults returned %d\r\n", ret);
    }
    mbedtls_ssl_conf_authmode( &connection->conf, MBEDTLS_SSL_VERIFY_NONE );
    mbedtls_ssl_conf_rng( &connection->conf, mbedtls_ctr_drbg_random, &network->ctr_drbg );
    mbedtls_ssl_conf_dbg( &connection->conf, my_debug, stdout );
    mbedtls_ssl_set_bio( &connection->ssl, connection,
                         mbedtls_net_send, mbedtls_net_recv, NULL );
    mbedtls_ssl_conf_psk_cb(&connection->conf, cb_check_psk, network);
    mbedtls_ssl_conf_dtls_cookies(&connection->conf,
                                  mbedtls_ssl_cookie_write,
                                  mbedtls_ssl_cookie_check,
                                  &network->cookies);
    mbedtls_ssl_set_timer_cb(&connection->ssl,connection,set_delay,get_delay);
    if( ( ret = mbedtls_ssl_setup (&connection->ssl,&connection->conf ) ) != 0 ){
        network_log_error("mbedtls_ssl_config_defaults returned %d\r\n", ret);
    }
    if( ( ret = mbedtls_ssl_set_client_transport_id(&connection->ssl,(void*)&connection->addr,sizeof(addr_t) ) ) != 0 ){
        network_log_error("mbedtls_ssl_config_defaults returned %d\r\n", ret);
    }
    return 0;
}
#endif

static inline connection_t* internal_create_server_connection(network_t* network, addr_t addr) {
    connection_t* connection = (connection_t *)lwm2m_malloc(sizeof(connection_t));
    if (connection == NULL)
    {
        network_log_error("memory alloc for new connection failed");
        return NULL;
    }
    memset(connection, 0, sizeof(connection_t));
    connection->network = network;
    connection->addr = addr;

    #ifdef LWM2M_WITH_DTLS
    connection->dtls = network->dtls;
    if (connection->dtls) {
        int ret;
        if ((ret = init_server_connection_ssl (connection,network))!=0){
            lwm2m_free(connection);
            return NULL;
        }
    }
    #endif
    internal_network_add_conn(network, connection);
    return connection;
}
#else
static inline connection_t* internal_create_server_connection(network_t* network, addr_t addr) {
    (void)network;
    (void)addr;
    return NULL;
}
#endif

connection_t * internal_connection_find(network_t * network, addr_t addr) {
    connection_t * connP = (connection_t*)network->connection_list;
    while (connP != NULL) {
        if (ip_equal(connP->addr, addr))
            return connP;
        connP = (connection_t*)connP->next;
    }
    if (connP == NULL && network->type == NET_SERVER_PROCESS) {
        return internal_create_server_connection(network, addr);
    }

    return NULL;
}

inline void internal_network_add_conn(network_t* network, connection_t* conn) {
    conn->next = (struct _connection_t *)network->connection_list;
    network->connection_list = conn;
}

int mbedtls_entropy_f_source(void *data, unsigned char *output, size_t len, size_t *olen) {
    (void)data;
    while (len>sizeof(long)) {
        int r = rand();
        memcpy(output,(void*)&r,sizeof(r));
        len -= sizeof(r);
        *olen += sizeof(r);
    }
    return 0;
}

uint8_t lwm2m_network_init(lwm2m_context_t * contextP, const char *localPort, bool dtls) {
    // The network can only be initialized once. We also need the userdata pointer
    // and therefore check if it is not used so far.
    if (contextP->userData != NULL)
    {
        return 0;
    }

    // Allocate memory for the network structure
    contextP->userData = lwm2m_malloc(sizeof(network_t));
    if (contextP->userData == NULL)
    {
        return 0;
    }

    network_t* network = (network_t*)contextP->userData;
    memset(network, 0, sizeof(network_t));

#ifndef LWM2M_WITH_DTLS
    if (dtls) return 0;
#else
    mbedtls_debug_set_threshold(1);
    network->dtls = dtls;
    // Always init all cryptographic functionality
    //mbedtls_x509_crt_init( &network->certs ); // Certificate chains for DTLS not yet supported
    mbedtls_ctr_drbg_init( &network->ctr_drbg );
    mbedtls_entropy_init( &network->entropy );
    static const unsigned char pers[] = "lwm2m_library";
    mbedtls_entropy_add_source (&network->entropy,mbedtls_entropy_f_source,
                                NULL,0,MBEDTLS_ENTROPY_SOURCE_STRONG);
    if(mbedtls_ctr_drbg_seed(&network->ctr_drbg, mbedtls_entropy_func,
                             &network->entropy, pers, sizeof(pers)) != 0 ) {
        network_log_error("mbedtls_ctr_drbg_seed failed\n" );
        return 0;
    }
    #if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY) && defined(LWM2M_SERVER_MODE)
    mbedtls_ssl_cookie_init(&network->cookies);
    if (mbedtls_ssl_cookie_setup(&network->cookies,mbedtls_ctr_drbg_random, &network->ctr_drbg)!=0) {
        network_log_error("mbedtls_ssl_cookie_setup failed\n" );
        return 0;
    }
    #endif
#endif

    uint8_t r = internal_init_sockets(contextP, network, localPort);
    if (!r) {
        contextP->userData = 0;
        lwm2m_free(network);
    }
    return r;
}


#ifdef LWM2M_WITH_DTLS
static inline void check_handshake_over(lwm2m_context_t* contextP, bool inHandshake,
                                        connection_t* connection ) {
    // If handshake is done after this received packet, reinit lwm2m if necessary
    if (inHandshake && connection->ssl.state == MBEDTLS_SSL_HANDSHAKE_OVER) {
        lwm2m_server_t * targetP = contextP->serverList;
        while (targetP != NULL) {
            if (targetP->shortID == connection->shortServerID) {
                if (targetP->status == STATE_REG_PENDING)
                    targetP->status = STATE_DEREGISTERED;
                contextP->state = STATE_REGISTER_REQUIRED;
                break;
            }
            targetP = targetP->next;
        }
    }
}

void internal_check_timer(lwm2m_context_t *contextP, struct timeval* next_event) {
    network_t* network = (network_t*)contextP->userData;
    if (!network->cached_next_timer_connection) return;

    struct timeval tmr_current;
    gettimeofday( &tmr_current, NULL );

    // cached_next_timer_connection always points to the next point in time of all connections
    if (timercmp(&network->cached_next_timer_connection->tmr_current,&tmr_current,<)) {
        network->cached_next_timer_connection = NULL;
        // check all connections
        connection_t* c = network->connection_list;
        while (c) {
            if (get_delay(c)==2){
                bool inHandshake = c->ssl.state != MBEDTLS_SSL_HANDSHAKE_OVER;
                int r = mbedtls_ssl_handshake(&c->ssl);
                check_handshake_over(contextP, inHandshake, c);
                if (r<0){
                    if (r==MBEDTLS_ERR_SSL_WANT_READ)
                        return;
                    network_log_error("mbedtls_ssl_handshake failed %i\r\n", r);
                }
            }
            c = c->next;
        }
    } else if (next_event) { // Adjust next_event
        struct timeval relative_next;
        timersub(&tmr_current,&network->cached_next_timer_connection->tmr_current,&relative_next);
        if (timercmp(&relative_next,next_event,<)) {
            *next_event = relative_next;
        }
    }
}
#else
void internal_check_timer(lwm2m_context_t *contextP, struct timeval* next_event) {}
#endif

void * lwm2m_connect_server(uint16_t secObjInstID, void * userData) {
    char * host;
    char * port;
    char uri[255];

    security_instance_t* secInst = lwm2m_get_security_object(secObjInstID);
    if (!secInst) return NULL;

    strncpy(uri, secInst->uri, sizeof (uri));

    network_log_info("Connecting to %s on %i\r\n", uri, secInst->shortID);

    uint8_t uri_result=decode_uri(uri, &host, &port);
    if (uri_result==0){
        network_log_error("Couldn't decode server uri %s.\r\n", uri);
        return NULL;
    }
    #ifndef LWM2M_WITH_DTLS
    else if (uri_result==2){
        network_log_error("dtls not supported: %s.\r\n", uri);
        return NULL;
    }
    #endif

    network_t* network = (network_t*)userData;
    if (network->type==NET_SERVER_PROCESS){
        network_log_error("lwm2m_connect_server not allowed on servers\n");
        return NULL;
    }
    connection_t * connection = internal_connection_create(network, host, port);
    if (connection == NULL) {
        network_log_error("Connection creation failed\n");
    }
    else {
        connection->network = network;
        connection->shortServerID = secInst->shortID;
        network->connection_list = connection;
        #ifdef LWM2M_WITH_DTLS
        connection->dtls = uri_result==2;
        if (connection->dtls) {
            int ret;
            mbedtls_ssl_init( &connection->ssl );
            mbedtls_ssl_config_init( &connection->conf );
            if( ( ret = mbedtls_ssl_config_defaults( &connection->conf,
                            MBEDTLS_SSL_IS_CLIENT,
                            MBEDTLS_SSL_TRANSPORT_DATAGRAM,
                            MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
            {
                network_log_error("mbedtls_ssl_config_defaults returned %d\r\n", ret);
                lwm2m_free(connection);
                return NULL;
            }
            mbedtls_ssl_conf_psk(&connection->conf,
                                 ( const unsigned char*)secInst->secretKey,secInst->secretKeyLen,
                                ( const unsigned char*) secInst->publicIdentity,secInst->publicIdLen);
            mbedtls_ssl_conf_authmode( &connection->conf, MBEDTLS_SSL_VERIFY_NONE );
            mbedtls_ssl_conf_rng( &connection->conf, mbedtls_ctr_drbg_random, &network->ctr_drbg );
            mbedtls_ssl_conf_dbg( &connection->conf, my_debug, stdout );
//            if( ( ret = mbedtls_ssl_set_hostname( &newConnP->ssl, "mbed TLS Server" ) ) != 0 ) {
//                network_log_error(" failed\n  ! mbedtls_ssl_set_hostname returned %d\n\n", ret);
//                lwm2m_free(newConnP);
//                return NULL;
//            }
            mbedtls_ssl_set_bio( &connection->ssl, connection,
                                 mbedtls_net_send, mbedtls_net_recv, NULL );
            mbedtls_ssl_set_timer_cb(&connection->ssl,connection,set_delay,get_delay);
            mbedtls_ssl_setup (&connection->ssl,&connection->conf );

            if( ( ret = mbedtls_ssl_handshake( &connection->ssl ) ) != 0 ) {
                if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE){
                    network_log_error("mbedtls_ssl_handshake failed %x\n", -ret);
                    lwm2m_free(connection);
                    return NULL;
                }
            }
        }
        #endif
    }

    return (void *)connection;
}

uint8_t lwm2m_buffer_send(void * sessionH,
                          uint8_t * buffer,
                          size_t length,
                          void * userdata)
{
    (void)userdata;
    connection_t * connection = (connection_t*) sessionH;

    if (connection == NULL)
    {
        network_log_error("failed sending %lu bytes, missing connection\r\n", (long unsigned)length);
        return COAP_500_INTERNAL_SERVER_ERROR ;
    }

    int r;
    #ifdef LWM2M_WITH_DTLS
    if (connection->dtls) {
        r = mbedtls_ssl_write(&connection->ssl, buffer, length);
        if (r==MBEDTLS_ERR_SSL_WANT_WRITE) r = 0;
    } else {
        r = mbedtls_net_send(connection, (const unsigned char*)buffer, length);
    }
    #else
    r = mbedtls_net_send(connection, (const unsigned char*)buffer, length);
    #endif
    return r>=0 ? COAP_NO_ERROR : COAP_503_SERVICE_UNAVAILABLE;
}

void internal_network_read(lwm2m_context_t* contextP, void *dest, size_t len, connection_t *connection) {
    ssize_t r;
    #ifdef LWM2M_WITH_DTLS
    network_t* network = (network_t*)contextP->userData;
    if (connection->dtls) {
        bool inHandshake = connection->ssl.state != MBEDTLS_SSL_HANDSHAKE_OVER;
        r = mbedtls_ssl_read(&connection->ssl, dest, (size_t)len);
        check_handshake_over(contextP, inHandshake, connection);
        if (r==MBEDTLS_ERR_SSL_WANT_READ)
            return;
        if (r<0){
            int ret;
            if (network->type==NET_SERVER_PROCESS &&
                    r==MBEDTLS_ERR_SSL_CLIENT_RECONNECT){
                ret=mbedtls_ssl_handshake(&connection->ssl);
                return;
            }
            if( ( ret = mbedtls_ssl_session_reset(&connection->ssl) ) != 0 ){
                network_log_error("mbedtls_ssl_session_reset returned %d\r\n", ret);
            }
            if (r==MBEDTLS_ERR_SSL_BAD_INPUT_DATA){
                network_log_error("MBEDTLS_ERR_SSL_BAD_INPUT_DATA!\n");
            }else
            if (r==MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED){
                network_log_info("MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED!\n");
            }else
                network_log_error("(ssl) receiving failed: %0x!\r\n", (int)-r);
            lwm2m_close_connection (connection,network);
            return;
        }
    } else {
        r = mbedtls_net_recv(connection, dest, (size_t)len);
    }
    #else
    r = mbedtls_net_recv(connection, dest, (size_t)len);
    if (r<0) {
        network_log_error("receiving failed: %i!\r\n", (int)r);
        return;
    }
    #endif
    len = (size_t)r;
    lwm2m_handle_packet(contextP, dest, (int)len, connection);
}

#ifdef LWM2M_WITH_DTLS
void lwm2m_close_connection_ssl(network_t* network, connection_t * t) {
    if (network->cached_next_timer_connection == t)
        network->cached_next_timer_connection = NULL;
    if(t->dtls){
        mbedtls_ssl_free( &t->ssl );
        mbedtls_ssl_config_free( &t->conf );
    }
}

void lwm2m_network_close_ssl(network_t* network) {
    mbedtls_ctr_drbg_free( &network->ctr_drbg );
    mbedtls_entropy_free( &network->entropy );
    #if defined(LWM2M_SERVER_MODE)
        #if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY)
            mbedtls_ssl_cookie_free ( &network->cookies );
        #endif
        lwm2m_free(network->publicIdentity);
        lwm2m_free(network->serverPublicKey);
        lwm2m_free(network->secretKey);
    #endif
}

#else
void lwm2m_close_connection_ssl(network_t* network, connection_t * t) {}
void lwm2m_network_close_ssl(network_t* network) {}
#endif

void lwm2m_close_connection(void * sessionH,
                            void * userData)
{
    network_t* network = (network_t*)userData;
    // Protect us from being released multiple times
    if (!network) return;
    connection_t * t = network->connection_list;

    // Remove connection from single linked list (search for entry if necessary)
    if(t==sessionH)
        network->connection_list=NULL;
    else while (t) {
        if (t->next == sessionH) {
            // Next extry would be the to-be-removed entry
            t->next = ((connection_t*)sessionH)->next;
            break;
        }
    }
    lwm2m_close_connection_ssl(network, ((connection_t*)sessionH));
    lwm2m_free(sessionH);
}

void lwm2m_network_close(lwm2m_context_t * contextP) {
    if (!contextP->userData) return;

    network_t* network = (network_t*)contextP->userData;

    // Close connections
    if ( network->connection_list) {
        connection_t * t = network->connection_list;
        while (t) {
            connection_t*next = (connection_t*)t->next;
            lwm2m_close_connection(t,network);
            t = next;
        }
    }

    // Close sockets
    for (unsigned c = 0; c < network->open_listen_sockets; ++c)
        closeSocket(network, c);
    network->open_listen_sockets = 0;

    lwm2m_network_close_ssl(network);

    lwm2m_free(network);
    contextP->userData = NULL;
}
