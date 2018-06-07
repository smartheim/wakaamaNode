#if !defined(LWIP) && (defined(_WIN32) || defined(__unix__) || defined(POSIX_NETWORK))

#include "liblwm2m.h"
#include "lwm2m_connect.h"
#include "lwm2m_objects.h"
#include "client_debug.h"
#include "network.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

bool network_init()
{
    return true;
}

void network_close()
{

}

void* network_get_interface(int id)
{
    (void)id;
    return 0;
}

uint8_t network_step_blocking(lwm2m_context_t * lwm2mH, int bound_sockets)
{
    struct timeval tv = {0,1000*50}; // wait 50ms for an incoming packet
    fd_set readfds = {{0}};
    for (uint8_t c = 0; c < bound_sockets; ++c) {
        int sock = lwm2m_network_native_sock(lwm2mH, c);
        if (sock == -1)
            return COAP_500_INTERNAL_SERVER_ERROR;
        FD_SET(sock, &readfds);
    }

    uint8_t result = lwm2m_step(lwm2mH, &tv.tv_sec);
    if (result != 0 && result != COAP_503_SERVICE_UNAVAILABLE)
    {
        fprintf(stderr, "lwm2m_step() failed: 0x%X\r\n", result);
    }

    /*
     * This part wait for an event on the socket until "tv" timed out (set
     * with the precedent function)
     */
    int select_result = select(FD_SETSIZE, &readfds, NULL, NULL, &tv);

    if (select_result < 0 && errno != EINTR)
    {
        fprintf(stderr, "Error in select(): %d %s\r\n", errno, strerror(errno));
        return COAP_500_INTERNAL_SERVER_ERROR;
    }

    for (uint8_t c = 0; c < bound_sockets; ++c)
    {
        int sock = lwm2m_network_native_sock(lwm2mH, c);
        if (sock == -1)
            return COAP_500_INTERNAL_SERVER_ERROR;
        if (select_result > 0 && FD_ISSET(sock, &readfds))
        {
            if (!lwm2m_network_process(lwm2mH)) {
                return COAP_500_INTERNAL_SERVER_ERROR;
            }
        }
    }

    return result;
}

#endif
