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
#if !defined(LWIP) && (defined(_WIN32) || defined(__unix__) || defined(POSIX_NETWORK))

#include "lwm2m/connect.h"
#include "lwm2m/objects.h"
#include "lwm2m/debug.h"
#include "lwm2m/network.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

bool test_network_init()
{
    return true;
}

void test_network_close()
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
        intptr_t sock = lwm2m_network_native_sock(lwm2mH, c);
        if (sock == -1)
            return COAP_500_INTERNAL_SERVER_ERROR;
        FD_SET(sock, &readfds);
    }

    int result = lwm2m_step(lwm2mH, &tv.tv_sec);
    if (result != 0 && result != COAP_503_SERVICE_UNAVAILABLE) {
        fprintf(stderr, "lwm2m_step() failed: 0x%X\r\n", result);
    }

    /*
     * This part wait for an event on the socket until "tv" timed out (set
     * with the precedent function)
     */
    int select_result = select(FD_SETSIZE, &readfds, NULL, NULL, &tv);

    if (select_result < 0 && errno != EINTR) {
        fprintf(stderr, "Error in select(): %d %s\r\n", errno, strerror(errno));
        return COAP_500_INTERNAL_SERVER_ERROR;
    }

    for (uint8_t c = 0; c < bound_sockets; ++c) {
        intptr_t sock = lwm2m_network_native_sock(lwm2mH, c);
        if (sock == -1)
            return COAP_500_INTERNAL_SERVER_ERROR;
        if (select_result > 0 && FD_ISSET(sock, &readfds)) {
            if (!lwm2m_network_process(lwm2mH, &tv)) {
                return COAP_500_INTERNAL_SERVER_ERROR;
            }
        }
    }

    return result;
}

#endif
