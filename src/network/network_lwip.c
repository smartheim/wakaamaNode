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
typedef int make_iso_compilers_happy; // if not LWIP

#ifdef LWIP

#include "lwm2m/network.h"
#include "lwm2m/c_connect.h"
#include "network_common.h"
#include "../wakaama/internals.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE 1024
#endif

#include "lwip/api.h"
#include "lwip/sys.h"
#include "lwip/udp.h"
#include "lwip/dns.h"

// it is either timers.h or since Jul 19, 2016 timeouts.h
//#include "lwip/timeouts.h"
//#include "lwip/timers.h"

void udp_raw_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

uint8_t internal_init_sockets(lwm2m_context_t * contextP, network_t* network, uint16_t localPort)
{
    if (localPort) {
        // Server
        network->type = NET_SERVER_PROCESS;
    } else {
        // client
        network->type = NET_CLIENT_PROCESS;
    }

    network->socket_handle[0].net_if_out = NULL;
    network->socket_handle[0].udp = udp_new();
    if (network->socket_handle[0].udp == NULL) {
        return 0;
    }

    udp_bind((udp_pcb_t*)network->socket_handle[0].udp, IP_ADDR_ANY, !localPort ? 12873 : localPort);
    udp_recv((udp_pcb_t*)network->socket_handle[0].udp, (udp_recv_fn)udp_raw_recv, contextP);
    network->open_listen_sockets = 1;

    return (uint8_t)network->open_listen_sockets;
}

bool __attribute__((weak)) lwm2m_network_process(lwm2m_context_t * contextP) {
    (void)contextP;
    internal_check_timer(contextP);
    return true;
}

void udp_raw_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    (void)pcb;
    if(p == NULL) return;

    lwm2m_context_t * contextP = (lwm2m_context_t*)arg;
    network_t* network = (network_t*)contextP->userData;

    uint8_t buffer[MAX_PACKET_SIZE];
    size_t numBytes = MAX_PACKET_SIZE;

    // Find connection with given address (or create it in server mode)
    addr_t t;
    t.port = port;
    t.addr = *addr;
    connection_t * connection = internal_connection_find(network, t);
    if (connection == NULL && network->type == NET_SERVER_PROCESS) {
        connection= internal_create_server_connection(network, t);
        #ifdef LWM2M_SERVER_MODE
        if (!connection->sock){
            for (unsigned i=0;i<network->open_listen_sockets;++i)
                if (network->socket_handle[i].udp==pcb){
                    connection->sock=&network->socket_handle[i];
                    break;
                }
            assert(connection->sock);
        }
        #endif
    }

    if (!connection) return;
    connection->addr = t;
    connection->p = p;

    internal_network_read(contextP, buffer, numBytes, connection);

    pbuf_free(p);
}

inline void internal_closeSocket(network_t* network, unsigned socket_handle) {
    udp_remove((udp_pcb_t*)network->socket_handle[socket_handle].udp);
}

void internal_network_close(network_t* network){(void)network;}


intptr_t lwm2m_network_native_sock(lwm2m_context_t * contextP, unsigned sock_no) {
    network_t* network = (network_t*)contextP->userData;
    if (!network) return -1;
    return (intptr_t)network->socket_handle[sock_no].udp;
}

#ifdef LWM2M_NETWORK_LOGGING
void connection_log_io(connection_t* connP, int length, bool sending) {
    #if LWIP_IPV4 && LWIP_IPV6
    static char destIP[40];
    const char* a = ipaddr_ntoa(&connP->addr.addr);
    strcpy(destIP, a);
    const char* b;
    struct netif * NetIf =(struct netif *)connP->network->socket_handle[0].net_if_out;
    if (NetIf)
    {
        b = connP->addr.addr.type==IPADDR_TYPE_V4 ?
                ipaddr_ntoa(netif_ip_addr4(NetIf)) :
                ipaddr_ntoa(netif_ip_addr6(NetIf, 0));
    }
    else
    {
        b = "N/A";
    }
    #elif LWIP_IPV4
    const char* a = ipaddr_ntoa(&connP->addr.addr);
    const char* b;
    if (connP->addr.net_if_out)
    {
        b = ipaddr_ntoa(((const ip_addr_t*)&(((struct netif *)connP->addr.net_if_out)->ip_addr)));
    }
    else
    {
        b = "N/A";
    }
    #elif LWIP_IPV6
    #else
    const char* a = "N/A";
    const char* b = "N/A";
    #endif

    if (sending)
        network_log_error("Sending %d bytes to [%s]:%u. Interface IP: %s. Is Server: %d\r\n", length, destIP,
            connP->addr.port, b, connP->network->type==NET_SERVER_PROCESS);
    else
        network_log_error("Receiving %d bytes to [%s]:%u. Interface IP: %s. Is Server: %d\r\n", length, destIP,
            connP->addr.port, b, connP->network->type==NET_SERVER_PROCESS);
}
#endif

int mbedtls_net_send(void *ctx, const unsigned char *buffer, size_t len) {
    connection_t * connection = (connection_t*)ctx;
    struct pbuf * pb = pbuf_alloc(PBUF_TRANSPORT, (u16_t)len, PBUF_REF);
    if (!pb) return MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL;
    pb->payload = (void*)buffer;

    err_t err;
    if (connection->sock->net_if_out)
        err = udp_sendto_if(connection->sock->udp, pb, &connection->addr.addr, connection->addr.port,
                            connection->sock->net_if_out);
    else
        err = udp_sendto(connection->sock->udp, pb, &connection->addr.addr, connection->addr.port);

    pbuf_free(pb); //De-allocate packet buffer

    if (err != ERR_OK)
    {
        network_log_error("failed sending %lu bytes\r\n", len);
        #ifdef LWM2M_WITH_DTLS
        return MBEDTLS_ERR_SSL_INTERNAL_ERROR;
        #else
        return COAP_500_INTERNAL_SERVER_ERROR;
        #endif
    } else
        connection_log_io(connection, (int)len, true);

    return (int)len;
}

int mbedtls_net_recv( void *ctx, unsigned char *buf, size_t len ) {
    connection_t * connection = (connection_t*)ctx;
    if (!connection->p || !connection->p->tot_len) {
        assert(connection->sock);
        #ifdef LWM2M_WITH_DTLS
        return MBEDTLS_ERR_SSL_WANT_READ;
        #else
        network_log_error("recvfrom failed %p", (void*)connection->sock->udp);
        return COAP_500_INTERNAL_SERVER_ERROR;
        #endif
    }
    
    len = len > connection->p->tot_len ? connection->p->tot_len : len;
    memcpy(buf, connection->p->payload, len);
    connection_log_io(connection, (int)len, false);

    // Consumed.
    connection->p = NULL;
    
    return (int)len;
}

inline bool ip_equal(addr_t a, addr_t b) {
    return ip_addr_cmp(&a.addr, &b.addr);
}

connection_t * internal_connection_create(network_t* network,
                                 char * host,
                                 uint16_t port)
{
    ip_addr_t addr;
    if (!ipaddr_aton(host, &addr))
    {
        return 0;
    }

    if (port == 0)
        return 0;

    connection_t * connection = (connection_t *)lwm2m_malloc(sizeof(connection_t));
    if (connection != NULL) {
        memset(connection, 0, sizeof(connection_t));
        connection->sock = &network->socket_handle[0];
        connection->addr.port = port;
        connection->addr.addr = addr;
        connection->next = (struct _connection_t *)network->connection_list;
    }

    return connection;
}

#endif
