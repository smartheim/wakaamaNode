#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "config.h"
#include "er-coap-13/er-coap-13.h"

typedef struct _lwm2m_context_t lwm2m_context_t;

// defined in packet.c
uint8_t message_send(lwm2m_context_t * contextP, coap_packet_t * message, void * sessionH);
