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
#include "network_common.h"

typedef int make_iso_compilers_happy; // if not POSIX_NETWORK

#ifdef POSIX_NETWORK

#include "lwm2m/network.h"
#include "lwm2m/c_connect.h"
#include "lwm2m/debug.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include "wepoll/wepoll.h"
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #include <Winsock2.h>
    #include <ws2tcpip.h>
    #define LOG_ERR 3
    typedef uint16_t in_port_t;
    #define close(s) closesocket(s)
#else
    #include <sys/epoll.h>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netdb.h>
#endif

inline void internal_closeSocket(network_t* network, unsigned socket_handle) {
    close(network->socket_handle[socket_handle].data.fd);
}

void internal_network_close(network_t* network){
    if (network->epfd)
        close(network->epfd);
}

uint8_t internal_init_sockets(lwm2m_context_t * contextP, network_t* network, uint16_t localPort) {
    (void)contextP;
    #ifdef _WIN32
    struct WSAData d;
    if (WSAStartup(MAKEWORD(2, 2), &d) != 0) {
        return -1;
    }
    #endif

    int s = -1;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *p;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0; // any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;


    int r;
    if (localPort) {
        // Server
        network->type = NET_SERVER_PROCESS;
        char port[7];
        snprintf(port, 7, "%d", localPort);
        r = getaddrinfo(NULL, port, &hints, &res);
    } else {
        // client
        network->type = NET_CLIENT_PROCESS;
        r = getaddrinfo(NULL, "12873", &hints, &res);
    }

    if (0 != r || res == NULL)
        return 0;

    network->open_listen_sockets = 0;
    for(p = res ; p != NULL && s == -1 ; p = p->ai_next)
        ++network->open_listen_sockets;

    network->epfd = epoll_create(LWM2M_MAX_SOCKETS);

    network->open_listen_sockets = 0;
    for(p = res ; p != NULL; p = p->ai_next)
    {
        int handle = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (handle >= 0)
        {
            if (-1 == bind(handle, p->ai_addr, p->ai_addrlen))
            {
                close(handle);
            } else
            {
                struct epoll_event *ev= &network->socket_handle[network->open_listen_sockets];
                ev->events=EPOLLIN | EPOLLPRI | EPOLLONESHOT;
                ev->data.fd=handle;
                errno=0;
                epoll_ctl(network->epfd, EPOLL_CTL_ADD, ev->data.fd, ev);
                assert (errno==0);

                ++network->open_listen_sockets;
                // Don't use more sockets than we have size in our array
                if ((unsigned long)network->open_listen_sockets > sizeof(network->socket_handle)/sizeof(int))
                    break;
            }
        }
    }

    freeaddrinfo(res);

    return (uint8_t)network->open_listen_sockets;
}


intptr_t lwm2m_network_native_sock(lwm2m_context_t * contextP, unsigned sock_no) {
    network_t* network = network_from_context(contextP);
    if (!network) return -1;
    return (intptr_t)network->socket_handle[sock_no].data.fd;
}

#ifdef LWM2M_NETWORK_LOGGING
void connection_log_io(connection_t* connection, int length, bool sending)
{
    const struct sockaddr_storage addr = connection->addr.addr;
    const network_process_type_t isServer = connection->network->type;

    char s[INET6_ADDRSTRLEN];
    in_port_t port=0;

    s[0] = 0;

    if (AF_INET == addr.ss_family)
    {
        struct sockaddr_in *saddr = (struct sockaddr_in *)&addr;
        inet_ntop(saddr->sin_family, &saddr->sin_addr, s, INET_ADDRSTRLEN);
        port = ntohs(saddr->sin_port);
    }
    else if (AF_INET6 == addr.ss_family)
    {
        struct sockaddr_in6 *saddr = (struct sockaddr_in6 *)&addr;
        inet_ntop(saddr->sin6_family, &saddr->sin6_addr, s, INET6_ADDRSTRLEN);
        port = ntohs(saddr->sin6_port);
    }

#ifdef LWM2M_WITH_DTLS
    const int ssl_handshake = connection->ssl.state;
#else
    const int ssl_handshake = 0;
#endif

    if (sending)
        network_log_info("Sending %d bytes to [%s]:%hu (server: %i, dtls handshake: %i )\r\n",
                (int)length, s, port, isServer, ssl_handshake);
    else
        network_log_info("Receiving %d bytes from [%s]:%hu (server: %i, dtls handshake: %i)\r\n",
                (int)length, s, port, isServer, ssl_handshake);

    //output_buffer(stderr, buffer, length, 0);
}
#endif

bool lwm2m_network_process(lwm2m_context_t * contextP) {
    network_t* network = network_from_context(contextP);
    for (unsigned c = 0; c < network->open_listen_sockets; ++c) {
        uint8_t buffer[MAX_PACKET_SIZE];
        size_t numBytes = MAX_PACKET_SIZE;
        struct sockaddr_storage addr={0};
        socklen_t addrLen = sizeof(addr);
        
        ssize_t r = recvfrom(network->socket_handle[c].data.fd, buffer, numBytes,
                         MSG_PEEK|MSG_DONTWAIT, (struct sockaddr *)&addr, &addrLen);

        if (r < 0)
        {
            if (errno!=EAGAIN)
                network_log_error("Error in recvfrom(): %d %s\r\n", errno, strerror(errno));
            errno=0;
            continue;
        } else if (r == 0)
            continue; // no new data

        // Find connection with given address (or create it in server mode)
        addr_t t;
        t.addr = addr;
        connection_t * connection = internal_connection_find(network, t);
        #ifdef LWM2M_SERVER_MODE
        if (connection == NULL && network->type == NET_SERVER_PROCESS) {
            connection= internal_create_server_connection(network, t);
        }
        #endif
        if (!connection) continue;
        connection->sock = &network->socket_handle[c];
        connection->addr = t;

        //connection_log_io(connection,r,false);
        internal_network_read(contextP, buffer, numBytes, connection);
    }
    internal_check_timer(contextP);
    return network->open_listen_sockets >= 1;
}

#define IPADDRSIZE(connP) (connP->addr.addr.ss_family==AF_INET?sizeof(struct sockaddr_in):sizeof(struct sockaddr_in6))
#define IPADDR(connP) (struct sockaddr *)&(connP->addr.addr)

int mbedtls_net_send(void *ctx, const unsigned char *buffer, size_t length) {
    connection_t * connection = (connection_t*)ctx;
    ssize_t nbSent = 0;
    size_t offset = 0;
    while (offset != length)
    {
        nbSent = sendto(connection->sock->data.fd, buffer + offset, length - offset, MSG_DONTWAIT,
                        IPADDR(connection), IPADDRSIZE(connection));

        connection_log_io(connection, (int)length, true);
        if (nbSent == -1)
            break;
        offset += (size_t)nbSent;
    }
    if (nbSent>=0) return (int)nbSent;
    if (errno==EAGAIN||errno==EWOULDBLOCK){
        errno=0;
        #ifdef LWM2M_WITH_DTLS
        return MBEDTLS_ERR_SSL_WANT_WRITE;
        #else
        return 0;
        #endif
    }
    network_log_error( "#> failed sending %lu bytes\r\n", length);
    #ifdef LWM2M_WITH_DTLS
    return MBEDTLS_ERR_SSL_INTERNAL_ERROR;
    #else
    return COAP_500_INTERNAL_SERVER_ERROR;
    #endif
}

int mbedtls_net_recv( void *ctx, unsigned char *buf, size_t len ) {
    connection_t * connection = (connection_t*)ctx;
    struct sockaddr_storage addr;
    socklen_t addrLen = sizeof(addr);

    errno=0;
    ssize_t r = recvfrom(connection->sock->data.fd, buf, len, MSG_DONTWAIT, (struct sockaddr *)&addr, &addrLen);
    if (r>=0) {
        connection_log_io(connection, (int)r, false);
        epoll_ctl(connection->network->epfd, EPOLL_CTL_MOD, connection->sock->data.fd, connection->sock);
        assert (errno==0);
        return (int)r;
    }
    if (errno==EAGAIN||errno==EWOULDBLOCK){
        errno=0;
        #ifdef LWM2M_WITH_DTLS
        return MBEDTLS_ERR_SSL_WANT_READ;
        #else
        return 0;
        #endif
    }
    network_log_error("recvfrom failed %i", (int)errno);
    assert (errno!=2); // The device should not be closed without any reason
    errno=0;
    #ifdef LWM2M_WITH_DTLS
    return MBEDTLS_ERR_SSL_INTERNAL_ERROR;
    #else
    return COAP_500_INTERNAL_SERVER_ERROR;
    #endif
}

sock_t* test_and_return_working_socket_handle(network_t* network,
                                          char * host,
                                          uint16_t port,
                                          struct sockaddr_storage* destip) {

    struct addrinfo hints;
    struct addrinfo *servinfo = NULL;
    struct addrinfo *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICSERV|AI_ADDRCONFIG;

    char portStr[7];
    snprintf(portStr, 7, "%d", port);
    if (0 != getaddrinfo(host, portStr, &hints, &servinfo) || servinfo == NULL)
        return NULL;

    // we test the various addresses with the sockets we know
    for(p = servinfo ; p != NULL; p = p->ai_next)
    {
        for (unsigned sock_no = 0; sock_no < network->open_listen_sockets; ++sock_no)
        {
            int handle = network->socket_handle[sock_no].data.fd;
            memcpy(destip, p->ai_addr, p->ai_addrlen);
            // We test if the given socket is able to connect to the ip address
            if (-1 != connect(handle, p->ai_addr, p->ai_addrlen))
            {
                // "Connection" possible. If you use connect on a udp socket, that
                // socket will only receive from the given address. To make the socket
                // listen to any address again, call connect with sa_family == AF_UNSPEC.
                struct sockaddr any_addr;
                any_addr.sa_family = AF_UNSPEC;
                connect(handle,&any_addr,sizeof(any_addr));

                freeaddrinfo(servinfo);
                return &network->socket_handle[sock_no];
            }
        }
    }

    if (NULL != servinfo) {
        freeaddrinfo(servinfo);
    }
    return NULL;
}

connection_t * internal_connection_create(network_t* network,
                                 char * host,
                                 uint16_t port)
{
    if (!network->open_listen_sockets)
        return NULL;

    connection_t * connection = NULL;
    struct sockaddr_storage destip={0};
    sock_t* s = test_and_return_working_socket_handle(network, host, port, &destip);
    if (s != NULL) {
        connection = (connection_t *)lwm2m_malloc(sizeof(connection_t));
        if (connection != NULL) {
            memset(connection, 0, sizeof(connection_t));
            connection->sock = s;
            connection->addr.addr = destip;
            connection->next = (struct _connection_t *)network->connection_list;
        }
    }

    return connection;
}

int lwm2m_block_wait(lwm2m_context_t * contextP, unsigned timeout_in_msec) {
    network_t* network = network_from_context(contextP);

    struct epoll_event rev;
    const int due_time_ms = network->due_time_ms;

    if (!timeout_in_msec) return 0;

    errno=0;
    int nfds = epoll_wait(network->epfd, &rev, 1, due_time_ms);

    network->due_time_ms = timeout_in_msec;

    if (nfds < 0 && errno != EINTR) {
        fprintf(stderr, "Error in epoll_wait(): %d %s\r\n", errno, strerror(errno));
        return -1;
    }

    return rev.data.fd;
}


/////// Compare IP addresses on POSIX systems

#define SOCK_ADDR_PTR(ptr)	((struct sockaddr *)(ptr))
#define SOCK_ADDR_FAMILY(ptr)	SOCK_ADDR_PTR(ptr)->sa_family

#define SOCK_ADDR_IN_PTR(sa)	((struct sockaddr_in *)(sa))
#define SOCK_ADDR_IN_ADDR(sa)	SOCK_ADDR_IN_PTR(sa)->sin_addr

#define SOCK_ADDR_LEN(sa) \
   (SOCK_ADDR_PTR(sa)->sa_family == AF_INET6 ? \
    sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in))

#define SOCK_ADDR_IN6_PTR(sa)	((struct sockaddr_in6 *)(sa))
#define SOCK_ADDR_IN6_ADDR(sa)	SOCK_ADDR_IN6_PTR(sa)->sin6_addr

#define SOCK_ADDR_EQ_ADDR(sa, sb) \
   ((SOCK_ADDR_FAMILY(sa) == AF_INET && SOCK_ADDR_FAMILY(sb) == AF_INET \
     && SOCK_ADDR_IN_ADDR(sa).s_addr == SOCK_ADDR_IN_ADDR(sb).s_addr) \
    || (SOCK_ADDR_FAMILY(sa) == AF_INET6 && SOCK_ADDR_FAMILY(sb) == AF_INET6 \
        && memcmp((char *) &(SOCK_ADDR_IN6_ADDR(sa)), \
                  (char *) &(SOCK_ADDR_IN6_ADDR(sb)), \
                  sizeof(SOCK_ADDR_IN6_ADDR(sa))) == 0))

inline bool ip_equal(addr_t a, addr_t b) {
    const struct sockaddr * sa = (struct sockaddr*)&a.addr;
    const struct sockaddr * sb = (struct sockaddr*)&b.addr;
    if (sa->sa_family != sb->sa_family) return false;

    if (sa->sa_family == AF_INET) {
        return 0==(SOCK_ADDR_IN_ADDR(sa).s_addr - SOCK_ADDR_IN_ADDR(sb).s_addr);
    } else if (sa->sa_family == AF_INET6) {
        return (0==memcmp((char *) &(SOCK_ADDR_IN6_ADDR(sa)),
               (char *) &(SOCK_ADDR_IN6_ADDR(sb)),
               sizeof(SOCK_ADDR_IN6_ADDR(sa))));
    } else {
        return false;
    }
}

#endif
