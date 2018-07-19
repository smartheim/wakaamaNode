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

#include "lwm2m/c_connect.h"
#include "lwm2m/network.h"
#include "lwm2m/debug.h"
#include "network_common.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef int make_iso_compilers_happy; // if not LWM2M_WITH_DTLS

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

    time_t tmr_current = lwm2m_gettime();
    connection->tmr_current = tmr_current;
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

    time_t tmr_current = lwm2m_gettime();
    elapsed_ms = (unsigned long)( tmr_current  - connection->tmr_current  ) * 1000ul;

    if( elapsed_ms >= connection->tmr_final_ms )
        return( 2 );

    if( elapsed_ms >= connection->tmr_intermediate_ms )
        return( 1 );

    // Adjust due_time if necessary
    if ((uint32_t)connection->network->due_time_ms > connection->tmr_final_ms)
        connection->network->due_time_ms = connection->tmr_final_ms;

    return( 0 );
}

static void my_debug( void *ctx, int level,
                      const char *file, int line, const char *str )
{
    (void) ctx;
    (void) level;
    (void) file;
    (void) line;
    (void) str;
    network_log_error("%s:%04d: %s", file, line, str);
}

#ifdef LWM2M_SERVER_MODE

static int cb_check_psk(void *parameter, mbedtls_ssl_context *ssl, const unsigned char *psk_identity, size_t identity_len) {
    network_t* network = (network_t*)parameter;
    (void)psk_identity;
    (void)identity_len;
    return mbedtls_ssl_set_hs_psk(ssl,(const unsigned char*)network->secretKey,network->secretKeyLen);
}

int init_server_connection_ssl(connection_t* connection, network_t* network) {
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

static int mbedtls_entropy_f_source(void *data, unsigned char *output, size_t len, size_t *olen) {
    (void)data;
    while (len>sizeof(long)) {
        int r = rand();
        memcpy(output,(void*)&r,sizeof(r));
        len -= sizeof(r);
        *olen += sizeof(r);
    }
    return 0;
}

bool internal_network_ssl_init(network_t* network) {
    mbedtls_debug_set_threshold(1);
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
        return false;
    }
    #if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY) && defined(LWM2M_SERVER_MODE)
    mbedtls_ssl_cookie_init(&network->cookies);
    if (mbedtls_ssl_cookie_setup(&network->cookies,mbedtls_ctr_drbg_random, &network->ctr_drbg)!=0) {
        network_log_error("mbedtls_ssl_cookie_setup failed\n" );
        return false;
    }
    #endif
    return true;
}

void internal_check_timer(lwm2m_context_t *contextP) {
    network_t* network = network_from_context(contextP);

    // check all connections
    connection_t* c = network->connection_list;
    while (c) {
        if (get_delay(c)==2){
            int r = mbedtls_ssl_handshake(&c->ssl);
            if (r<0){
                if (r==MBEDTLS_ERR_SSL_TIMEOUT){
                    if (c->ssl.state<=MBEDTLS_SSL_CLIENT_HELLO)
                        network->handshakeState= DTLS_HANDSHAKE_TIMEOUT;
                    else
                        network->handshakeState= DTLS_HANDSHAKE_ABORTED;
                    continue;
                }
                if (r==MBEDTLS_ERR_SSL_WANT_READ)
                    continue;
                network_log_error("mbedtls_ssl_handshake failed %i\r\n", r);
            } else {
                if (!c->dtls || c->ssl.state==MBEDTLS_SSL_HANDSHAKE_OVER){
                    network->handshakeState= DTLS_NO_HANDSHAKE_IN_PROGRESS;
                }else
                    network->handshakeState= DTLS_HANDSHAKE_IN_PROGRESS;
            }
        }
        c = c->next;
    }
}

connection_t * internal_configure_ssl(connection_t * connection,
                                             network_t* network,
                                             security_instance_t* secInst) {
    if (connection->dtls) {
        int ret;
        mbedtls_ssl_init( &connection->ssl );
        mbedtls_ssl_config_init( &connection->conf );
        mbedtls_ssl_conf_handshake_timeout( &connection->conf,1000,30000 );
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

        network->handshakeState = DTLS_HANDSHAKE_IN_PROGRESS;
        if( ( ret = mbedtls_ssl_handshake( &connection->ssl ) ) != 0 ) {
            if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE){
                network->handshakeState = DTLS_HANDSHAKE_ABORTED;
                network_log_error("mbedtls_ssl_handshake failed %x\n", -ret);
                lwm2m_free(connection);
                return NULL;
            }
        }
    }
    return connection;
}

enum DtlsHandshakeState lwm2m_dtls_handshake_state(lwm2m_context_t *contextP){
    network_t* network = network_from_context(contextP);
    return network->handshakeState;
}

void internal_close_connection_ssl(network_t* network, connection_t * t) {
    if(t->dtls){
        mbedtls_ssl_free( &t->ssl );
        mbedtls_ssl_config_free( &t->conf );
    }
}

void internal_network_close_ssl(network_t* network) {
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

void internal_network_read(lwm2m_context_t* contextP, void *dest, size_t len, connection_t *connection) {
    ssize_t r;
    network_t* network = network_from_context(contextP);
    if (connection->dtls) {
        r = mbedtls_ssl_read(&connection->ssl, dest, (size_t)len);

        if (connection->ssl.state==MBEDTLS_SSL_HANDSHAKE_OVER){
            network->handshakeState= DTLS_NO_HANDSHAKE_IN_PROGRESS;
        }else
            network->handshakeState= DTLS_HANDSHAKE_IN_PROGRESS;

        if (r==MBEDTLS_ERR_SSL_WANT_READ)
            return;
        if (r<0){
            int ret;
            if (network->type==NET_SERVER_PROCESS &&
                    r==MBEDTLS_ERR_SSL_CLIENT_RECONNECT){
                if( ( ret = mbedtls_ssl_handshake(&connection->ssl) ) != 0 ){
                    network_log_error("mbedtls_ssl_handshake returned %d\r\n", ret);
                }
                return;
            }

            switch(r) {
                case MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED:
                    network_log_info("MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED!\n");
                    if( ( ret = mbedtls_ssl_session_reset(&connection->ssl) ) != 0 ){
                        network_log_error("mbedtls_ssl_session_reset returned %d\r\n", ret);
                    }
                    #ifdef LWM2M_SERVER_MODE
                    if( network->type==NET_SERVER_PROCESS &&
                            ( ret = mbedtls_ssl_set_client_transport_id(&connection->ssl,(void*)&connection->addr,sizeof(addr_t) ) ) != 0 ){
                        network_log_error("mbedtls_ssl_config_defaults returned %d\r\n", ret);
                    }
                    #endif
                    break;
            case MBEDTLS_ERR_SSL_BAD_INPUT_DATA:
                assert(1==0);
            default:
                network_log_error("(ssl) receiving failed: %0x!\r\n", (int)-r);
                internal_close_connection_ssl(network, connection);
            }
            return;
        }
    } else {
        r = mbedtls_net_recv(connection, dest, (size_t)len);
    }
    lwm2m_handle_packet(contextP, dest, (int)r, connection);
}

#endif
