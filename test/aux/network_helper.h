#pragma once

#include <stdint.h>
#include "wakaama/liblwm2m.h"
#ifdef __cplusplus
extern "C" {
#endif

// Uses lwm2m_step() to figure out what needs to be send and
// receives from the network stack and input traffic into wakaama via lwm2m_handle_packet().
uint8_t network_step_blocking(lwm2m_context_t * lwm2mH, int bound_sockets);

// Return true for success or if already initialized and false on error
bool network_init();

// Frees all network ressources, that were acquired in network_init()
void network_close();

void* network_get_interface(int id);

#ifdef __cplusplus
}
#endif
