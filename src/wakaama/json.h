#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "config.h"
#include "uri.h"
#include "data.h"

// defined in json.c
#ifdef LWM2M_SUPPORT_JSON
int json_parse(lwm2m_uri_t * uriP, const uint8_t *buffer, size_t bufferLen, lwm2m_data_t ** dataP);
int json_serialize(lwm2m_uri_t * uriP, int size, lwm2m_data_t * tlvP, uint8_t ** bufferP);
#endif
