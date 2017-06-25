#if !defined(LWIP) && (defined(_WIN32) || defined(__unix__))

#include "wakaama_network.h"
#include "wakaama_simple_client.h"
#include "network_utils.h"
#include "internals.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE 1024
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#define LOG_ERR 3
typedef uint16_t in_port_t;
#define close(s) closesocket(s)
#else
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#endif

typedef struct _connection_t_
{
    struct _connection_t *  next;
    int                     sock;
    struct sockaddr_in6     addr;
    size_t                  addrLen;
} connection_t;

connection_t * connection_find(connection_t * connList, struct sockaddr_storage * addr, size_t addrLen);
connection_t * connection_create(network_t * network, char * host, char * port);
void connection_free(connection_t * connList);

uint8_t lwm2m_network_init(lwm2m_context_t * contextP, const char *localPort) {
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
        r = getaddrinfo(NULL, localPort, &hints, &res);
    } else {
        // client
        network->type = NET_CLIENT_PROCESS;
        r = getaddrinfo(NULL, "12873", &hints, &res);
    }

    if (0 != r || res == NULL)
    {
        return -1;
    }

    network->open_listen_sockets = 0;
    for(p = res ; p != NULL && s == -1 ; p = p->ai_next)
        ++network->open_listen_sockets;

    network->socket_handle = (int*)malloc(sizeof(int)*network->open_listen_sockets);

    network->open_listen_sockets = 0;
    for(p = res ; p != NULL; p = p->ai_next)
    {
        network->socket_handle[network->open_listen_sockets] = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (network->socket_handle[network->open_listen_sockets] >= 0)
        {
            if (-1 == bind(network->socket_handle[network->open_listen_sockets], p->ai_addr, p->ai_addrlen))
            {
                close(network->socket_handle[network->open_listen_sockets]);
                network->socket_handle[network->open_listen_sockets] = -1;
            } else
            {
                ++network->open_listen_sockets;
            }
        }
    }

    freeaddrinfo(res);

    return network->open_listen_sockets;
}

#ifdef LWM2M_WITH_LOGS
void prv_log_addr(connection_t * connP, size_t length, bool sending)
{
    char s[INET6_ADDRSTRLEN];
    in_port_t port;

    s[0] = 0;

    if (AF_INET == connP->addr.sin6_family)
    {
        struct sockaddr_in *saddr = (struct sockaddr_in *)&connP->addr;
        inet_ntop(saddr->sin_family, &saddr->sin_addr, s, INET6_ADDRSTRLEN);
        port = saddr->sin_port;
    }
    else if (AF_INET6 == connP->addr.sin6_family)
    {
        struct sockaddr_in6 *saddr = (struct sockaddr_in6 *)&connP->addr;
        inet_ntop(saddr->sin6_family, &saddr->sin6_addr, s, INET6_ADDRSTRLEN);
        port = saddr->sin6_port;
    }

    if (sending)
        printf("Sending %d bytes to [%s]:%hu\r\n", length, s, ntohs(port));
    else
        printf("Receiving %d bytes from [%s]:%hu\r\n", length, s, ntohs(port));

    //output_buffer(stderr, buffer, length, 0);
}
#else
#define prv_log_addr(...) {}
#endif

bool __attribute__((weak)) lwm2m_network_process(lwm2m_context_t * contextP) {
    network_t* network = (network_t*)contextP->userData;
    uint8_t buffer[MAX_PACKET_SIZE];
    int numBytes;
    struct sockaddr_storage addr;
    socklen_t addrLen = sizeof(addr);

    for (unsigned c = 0; c < network->open_listen_sockets; ++c)
    {
        numBytes = recvfrom(network->socket_handle[c], buffer, MAX_PACKET_SIZE, 0, (struct sockaddr *)&addr, &addrLen);

        if (numBytes < 0)
        {
            simple_lwm2m_printf("Error in recvfrom(): %d %s\r\n", errno, strerror(errno));
            continue;
        } else if (numBytes == 0)
            continue; // no new data

        connection_t * connP = connection_find(network->connection_list, &addr, addrLen);

        if (connP == NULL && network->type == NET_SERVER_PROCESS) {
            connP = (connection_t *)malloc(sizeof(connection_t));
            if (connP == NULL)
            {
                simple_lwm2m_printf("memory alloc for new connection failed");
                continue;
            }

            connP->sock = network->socket_handle[c];
            memcpy(&(connP->addr), (struct sockaddr *)&addr, addrLen);
            connP->addrLen = addrLen;
            connP->next = (struct _connection_t *)network->connection_list;
            network->connection_list = connP;
        }

        if (connP != NULL) {
            prv_log_addr(connP, numBytes, false);
            lwm2m_handle_packet(contextP, buffer, numBytes, connP);
        } else {
            simple_lwm2m_printf("received bytes ignored!\r\n");
        }
    }

    return network->open_listen_sockets >= 1;
}

void __attribute__((weak)) lwm2m_network_close(lwm2m_context_t * contextP) {
    network_t* network = (network_t*)contextP->userData;
    for (unsigned c = 0; c < network->open_listen_sockets; ++c)
    {
        close(network->socket_handle[c]);
    }
    free(network->socket_handle);
    network->open_listen_sockets = 0;
    free(network);
    contextP->userData = NULL;
}

uint8_t lwm2m_buffer_send(void * sessionH,
                          uint8_t * buffer,
                          size_t length,
                          void * userdata)
{
    //network_t* network = (network_t*)userdata;
    connection_t * connP = (connection_t*) sessionH;

    if (connP == NULL)
    {
        fprintf(stderr, "#> failed sending %lu bytes, missing connection\r\n", length);
        return COAP_500_INTERNAL_SERVER_ERROR ;
    }

    prv_log_addr(connP, length, true);

    int nbSent;
    size_t offset = 0;
    while (offset != length)
    {
        nbSent = sendto(connP->sock, buffer + offset, length - offset, 0, (struct sockaddr *)&(connP->addr), connP->addrLen);
        if (nbSent == -1)
        {
            fprintf(stderr, "#> failed sending %lu bytes\r\n", length);
            return COAP_500_INTERNAL_SERVER_ERROR ;
        }
        offset += nbSent;
    }

    return COAP_NO_ERROR;
}

bool lwm2m_session_is_equal(void * session1,
                            void * session2,
                            void * userData)
{
    return (session1 == session2);
}

void * lwm2m_connect_server(uint16_t secObjInstID,
                            void * userData)
{

    char * host;
    char * port;
    char uri[255];

    if (!lwm2m_get_server_uri(secObjInstID, uri, sizeof(uri)))
        return NULL;

    simple_lwm2m_printf("Connecting to %s\r\n", uri);

    decode_uri(uri, &host, &port);

    network_t* network = (network_t*)userData;
    connection_t * newConnP = connection_create(network, host, port);
    if (newConnP == NULL) {
        fprintf(stderr, "Connection creation failed.\r\n");
    }
    else {
        network->connection_list = newConnP;
    }

    return (void *)newConnP;
}

void lwm2m_close_connection(void * sessionH,
                            void * userData)
{
    network_t* network = (network_t*)userData;
    connection_free(network->connection_list);
}

void lwm2m_network_force_interface(lwm2m_context_t * contextP, void* interface)
{
    // do nothing for posix sockets
}

connection_t * connection_find(connection_t * connList,
                               struct sockaddr_storage * addr,
                               size_t addrLen)
{
    connection_t * connP;

    connP = connList;
    while (connP != NULL)
    {
        if ((connP->addrLen == addrLen)
         && (memcmp(&(connP->addr), addr, addrLen) == 0))
        {
            return connP;
        }
        connP = (connection_t*)connP->next;
    }

    return connP;
}

connection_t * connection_create(network_t* network,
                                 char * host,
                                 char * port)
{
    if (!network->open_listen_sockets)
        return NULL;

    struct addrinfo hints;
    struct addrinfo *servinfo = NULL;
    struct addrinfo *p;
    int s;
    struct sockaddr *sa;
    socklen_t sl;
    connection_t * connP = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICSERV|AI_ADDRCONFIG;

    if (0 != getaddrinfo(host, port, &hints, &servinfo) || servinfo == NULL)
        return NULL;

    // we test the various addresses with the sockets we know
    s = -1;
    for(p = servinfo ; p != NULL; p = p->ai_next)
    {
        for (unsigned sock_no = 0; sock_no < network->open_listen_sockets; ++sock_no)
        {
            s = network->socket_handle[sock_no];
            sa = p->ai_addr;
            sl = p->ai_addrlen;
            // We test if the given socket is able to connect to the ip address
            if (-1 != connect(s, p->ai_addr, p->ai_addrlen))
            {
                // "Connection" possible. If you use connect on a udp socket, that
                // socket will only receive from the given address. To make the socket
                // listen to any address again, call connect with sa_family == AF_UNSPEC.
                struct sockaddr any_addr;
                any_addr.sa_family = AF_UNSPEC;
                connect(s,&any_addr,sizeof(any_addr));
                break;
            } else
                s = -1;
        }
    }

    if (s >= 0)
    {
        connP = (connection_t *)malloc(sizeof(connection_t));
        if (connP != NULL)
        {
            connP->sock = s;
            memcpy(&(connP->addr), sa, sl);
            connP->addrLen = sl;
            connP->next = (struct _connection_t *)network->connection_list;
        }
    }

    if (NULL != servinfo) {
        freeaddrinfo(servinfo);
    }

    return connP;
}

void connection_free(connection_t * connList)
{
    while (connList != NULL)
    {
        connection_t * nextP;

        nextP = (connection_t*)connList->next;
        free(connList);

        connList = nextP;
    }
}

#endif
