#pragma once

#include <stdint.h>
#include "wakaama/liblwm2m.h"
#ifdef __cplusplus
extern "C" {
#endif

uint8_t network_step_blocking(lwm2m_context_t * lwm2mH, int bound_sockets);
void network_init();
void network_close();
void* network_get_interface(int id);

#ifdef __cplusplus
}
#endif
