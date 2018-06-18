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
#include "../../wakaama/liblwm2m.h"

#ifndef LWM2M_DEFAULT_SERVER_PORT
#define LWM2M_DEFAULT_SERVER_PORT "5683"
#endif

#ifndef LWM2M_DEFAULT_SECURE_SERVER_PORT
#define LWM2M_DEFAULT_SECURE_SERVER_PORT "5684"
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct timeval;

#include <stdbool.h>

/**
 * @brief Initializes the network layer
 *
 * @param contextP  The wakaama context. Network socket information is stored in the
 *                  contexts userdata.
 * @param localPort Must be NULL/nullptr for clients in which case a port is automatically choosen.
 *                  For servers LWM2M_DEFAULT_SERVER_PORT/LWM2M_DEFAULT_SECURE_SERVER_PORT is recommended.
 * @param secure    Use DTLS if true. Method will return 0 if enabled and DTLS is not compiled in via LWM2M_WITH_DTLS.
 * @return Return 0 if socket binding failed. Otherwise returns the number
 *     of sockets the method could bind to (for IPv4 and IPv6 each on all available interfaces).
 */
uint8_t lwm2m_network_init(lwm2m_context_t * contextP, const char* localPort, bool secure);

/**
 * @brief Return the native socket handler for the given socket number.
 * Usually this method is relevant if posix sockets are used and you need the socket handlers for select().
 * @param contextP The wakaama context.
 * @param sock_no Number from 0..v-1 where v has been returned by lwm2m_network_init().
 * @return Native socket handler for the given socket number
 */
intptr_t lwm2m_network_native_sock(lwm2m_context_t * contextP, uint8_t sock_no);

/**
 * @brief lwm2m_network_process
 * Processes incoming network traffic and calls lwm2m_handle_packet.
 * @param contextP The wakaama context.
 * @param timeoutInSec Returns an optional timeout value that tells you when the next call is due.
 * Does not modify timeout if it already has a value that is sooner than the next due time.
 * For the DTLS handshake to be successful, it is required that you call lwm2m_network_process()
 * when the timeout has happened.
 * @return Return false if no open sockets are available.
 */
bool lwm2m_network_process(lwm2m_context_t * contextP, struct timeval* timeout);

/**
 * @brief Closes all opened sockets and clean context->userdata.
 * @param contextP The wakaama context.
 */
void lwm2m_network_close(lwm2m_context_t * contextP);

/**
 * @brief Force the network stack to use the given network interface
 * This is useful for testing purposes. The routing table will be ignored
 * and the given interface will be used for outgoing traffic.
 * @param contextP The wakaama context.
 * @param interface A generic value which can be used to point to a network
 * interface. The interpretation depends on the network backend.
 */
void lwm2m_network_force_interface(lwm2m_context_t * contextP, void* interface);

#ifdef __cplusplus
}
#endif
