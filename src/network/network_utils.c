#include <string.h>
#include "wakaama_network.h"
#include "network_utils.h"

uint8_t decode_uri(char* uri, char** host, char** port)
{
    // parse uri in the form "coaps://[host]:[port]"
    if (0 == strncmp(uri, "coaps://", strlen("coaps://")))
    {
        *host = uri+strlen("coaps://");
    }
    else if (0 == strncmp(uri, "coap://", strlen("coap://")))
    {
        *host = uri+strlen("coap://");
    }
    else
    {
        return 0;
    }
    char* afterHost = strrchr(*host, ':');
    *port = afterHost;
    if (*port == NULL) {
        *port = LWM2M_DEFAULT_SERVER_PORT;
        afterHost = *host + strlen(*host);
    } else {
        // split strings
        **port = 0;
        *port++;

    }

    // remove brackets
    if (*host[0] == '[')
    {
        *host++;
        if (*(afterHost - 1) == ']')
        {
            *(afterHost - 1) = 0;
        }
        else
            return 0;
    }
    return 1;
}

int __attribute__((weak)) lwm2m_network_native_sock(lwm2m_context_t * contextP, uint8_t sock_no) {
    network_t* network = (network_t*)contextP->userData;
    if (!network || !network->socket_handle)
        return -1;
    return network->socket_handle[sock_no];
}

void __attribute__((weak)) lwm2m_network_force_interface(lwm2m_context_t * contextP, void* interface)
{
    network_t* network = (network_t*)contextP->userData;
    network->net_if_out = interface;
}
