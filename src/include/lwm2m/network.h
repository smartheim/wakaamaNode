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
#define LWM2M_DEFAULT_SERVER_PORT 5683
#endif

#ifndef LWM2M_DEFAULT_SECURE_SERVER_PORT
#define LWM2M_DEFAULT_SECURE_SERVER_PORT 5684
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct timeval;

#include <stdbool.h>

/**
 * @brief Initializes the network layer
 *
 * Initializes the required udp sockets for the lwm2m communication to work.
 *
 * Is automatically called by the connect API, especially lwm2m_client_init().
 *
 * @param contextP  The wakaama context. Network socket information is stored in the
 *                  contexts userdata.
 * @param localPort Must be0 for clients in which case a port is automatically choosen.
 *                  For servers LWM2M_DEFAULT_SERVER_PORT/LWM2M_DEFAULT_SECURE_SERVER_PORT is recommended.
 * @return Return 0 if socket binding failed. Otherwise returns the number
 *     of sockets the method could bind to (for IPv4 and IPv6 each on all available interfaces).
 */
uint8_t lwm2m_network_init(lwm2m_context_t * contextP, uint16_t localPort);

/**
 * @brief Processes incoming network traffic and calls lwm2m_handle_packet
 *
 * Is automatically called by the connect API, especially lwm2m_process().
 *
 * @param contextP The wakaama context.
 * @param next_event Returns a timeout value that tells you when the next call is due.
 * Does not modify timeout if it already has a value that is sooner than the next due time.
 * For the DTLS handshake to be successful, it is required that you call lwm2m_network_process()
 * when the timeout has happened.
 * @return Return false if no open sockets are available.
 */
bool lwm2m_network_process(lwm2m_context_t * contextP, struct timeval* next_event);

/**
 * @brief Closes all opened sockets and clean context->userdata.
 *
 * Is automatically called by the connect API, especially lwm2m_client_close().
 *
 * @param contextP The wakaama context.
 */
void lwm2m_network_close(lwm2m_context_t * contextP);

/**
 * @brief Return the native socket handler for the given socket number.
 *
 * This method is relevant for posix sockets.
 * Those are used in a non-blocking way within this library.
 * Use the returned native socket handlers for select/poll().
 *
 * @param contextP The wakaama context.
 * @param sock_no Number from 0..v-1 where v has been returned by lwm2m_network_init().
 * @return Native socket handler for the given socket number
 */
intptr_t lwm2m_network_native_sock(lwm2m_context_t * contextP, unsigned sock_no);

/**
 * @brief Force the network stack to use the given network interface
 * This is useful for testing purposes. The routing table will be ignored
 * and the given interface will be used for outgoing traffic.
 * @param contextP The wakaama context.
 * @param interface A generic value which can be used to point to a network
 * interface. The interpretation depends on the network backend.
 */
void lwm2m_network_force_interface(lwm2m_context_t * contextP, void* interface);

/**
 * @brief Blocks until new data is available on the sockets
 *
 * This is only available on systems that have an epoll API call
 * (and on Windows with an emulated epoll API) with POSIX sockets.
 *
 * Call lwm2m_process() after this method returned.
 *
 * @param contextP Wakaama context
 * @param next_event The sleep time until the next event is due
 * @return Returns the socket number that received a message or 0 if it was a timeout. -1 on error.
 */
int lwm2m_block_wait(lwm2m_context_t * contextP, struct timeval next_event);

#ifdef __cplusplus
}
#endif
