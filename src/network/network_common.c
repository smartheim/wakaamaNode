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
#include <sys/time.h>

uint8_t decode_uri(char* uri, char** host, uint16_t* port)
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
    char* portStr = afterHost;
    if (portStr == NULL) {
        *port = r==1?LWM2M_DEFAULT_SERVER_PORT:LWM2M_DEFAULT_SECURE_SERVER_PORT;
        afterHost = *host + strlen(*host);
    } else {
        // split strings, by making the colon a c-string terminator
        *afterHost = 0;
        *port = (uint16_t)atoi(portStr+1);
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

bool lwm2m_session_is_equal(void * session1,
                            void * session2,
                            void * userData)
{
    (void)userData;
    return (session1 == session2);
}

#ifdef LWM2M_SERVER_MODE

connection_t* internal_create_server_connection(network_t* network, addr_t addr) {
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
    connection->dtls = network->publicIdLen;
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
connection_t* internal_create_server_connection(network_t* network, addr_t addr) {
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
    return NULL;
}

inline void internal_network_add_conn(network_t* network, connection_t* conn) {
    conn->next = (struct _connection_t *)network->connection_list;
    network->connection_list = conn;
}

uint8_t lwm2m_network_init(lwm2m_context_t * contextP, uint16_t localPort) {
    // The network can only be initialized once. We also need the userdata pointer
    // and therefore check if it is not used so far.
    if (contextP->userData != NULL)
        return 0;

    // Allocate memory for the network structure
    contextP->userData = lwm2m_malloc(sizeof(network_t));
    if (contextP->userData == NULL)
        return 0;

    network_t* network = network_from_context(contextP);
    memset(network, 0, sizeof(network_t));

#ifdef LWM2M_WITH_DTLS
    if (!internal_network_ssl_init(network)) return 0;
#endif

    uint8_t r = internal_init_sockets(contextP, network, localPort);
    if (!r) {
        contextP->userData = NULL;
        lwm2m_free(network);
    }
    return r;
}

void * lwm2m_connect_server(uint16_t secObjInstID, lwm2m_context_t * context) {
    char * host;
    uint16_t port;
    char uri[255];

    security_instance_t* secInst = lwm2m_get_security_object(context, secObjInstID);
    if (!secInst) return NULL;

    secInst->securityMode = LWM2M_SECURITY_MODE_NONE;

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
    #else
    if (uri_result==2){ // use dtls
        if (secInst->securityMode==LWM2M_SECURITY_MODE_PRE_SHARED_KEY &&
                (secInst->publicIdLen==0||secInst->secretKeyLen==0)){
            network_log_error("dtls preshared key information missing: %s.\r\n", uri);
            return NULL;
        }
    } else { // no enc
        internal_erase_security_params(secInst);
    }
    #endif

    network_t* network = (network_t*)context->userData;
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
        internal_network_add_conn (network,connection);
        #ifdef LWM2M_WITH_DTLS
        if (uri_result==2){
            connection->dtls = true;
            return internal_configure_ssl(connection,network,secInst);
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

#ifndef LWM2M_WITH_DTLS
inline void internal_close_connection_ssl(network_t* network, connection_t * t) {}
inline void internal_network_close_ssl(network_t* network) {}
void internal_check_timer(lwm2m_context_t *contextP, struct timeval* next_event) {}

void internal_network_read(lwm2m_context_t* contextP, void *dest, size_t len, connection_t *connection) {
    ssize_t r = mbedtls_net_recv(connection, dest, (size_t)len);
    if (r<0) {
        network_log_error("receiving failed: %i!\r\n", (int)r);
        return;
    }
    len = (size_t)r;
    lwm2m_handle_packet(contextP, dest, (int)len, connection);
}

inline bool internal_in_dtls_handshake(lwm2m_context_t *contextP){
    return false;
}

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
    internal_close_connection_ssl(network, ((connection_t*)sessionH));
    lwm2m_free(sessionH);
}

void lwm2m_network_close(lwm2m_context_t * contextP) {
    if (!contextP->userData) return;

    network_t* network = network_from_context(contextP);

    // Close all connections that are not already closed by lwm2m_close()
    if ( network->connection_list) {
        connection_t * t = network->connection_list;
        while (t) {
            connection_t*next = (connection_t*)t->next;
            lwm2m_close_connection(t,network);
            t = next;
        }
        network->connection_list=NULL;
    }

    // Close sockets
    for (unsigned c = 0; c < network->open_listen_sockets; ++c)
        internal_closeSocket(network, c);
    network->open_listen_sockets = 0;

    internal_network_close_ssl(network);

    internal_network_close(network);

    lwm2m_free(network);
    contextP->userData = NULL;
}
