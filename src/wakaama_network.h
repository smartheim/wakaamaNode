#pragma once
#include "wakaama/liblwm2m.h"

#ifndef LWM2M_DEFAULT_SERVER_PORT
#define LWM2M_DEFAULT_SERVER_PORT "5683"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/**
 * @brief Initializes the network layer
 *
 * @param contextP  The wakaama context. Network socket information is stored in the
 *                  contexts userdata.
 * @param localPort Must be NULL for clients in which case a port is automatically choosen.
 *                  For servers LWM2M_DEFAULT_SERVER_PORT is recommended.
 * @return Return 0 if socket binding failed. Otherwise returns the number
 *     of sockets we could bind to (for IPv4 and IPv6 each on all available interfaces).
 */
uint8_t lwm2m_network_init(lwm2m_context_t * contextP, const char* localPort);

/**
 * @brief Return the native socket handler for the given socket number.
 * Usually this method is relevant if posix sockets are used and you need the socket handlers for select().
 * @param contextP The wakaama context.
 * @param sock_no Number from 0..v-1 where v has been returned by lwm2m_network_init().
 * @return Native socket handler for the given socket number
 */
int lwm2m_network_native_sock(lwm2m_context_t * contextP, uint8_t sock_no);

/**
 * @brief lwm2m_network_process
 * Processes incoming network traffic and calls lwm2m_handle_packet.
 * @param contextP The wakaama context.
 * @return Return false if no open sockets are available.
 */
bool lwm2m_network_process(lwm2m_context_t * contextP);

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
