#pragma once
#include "wakaama/liblwm2m.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LWM2M_WITH_LOGS
#define lwm2m_printf(...)
#endif

void print_state(lwm2m_context_t * lwm2mH);

#ifdef __cplusplus
}
#endif
