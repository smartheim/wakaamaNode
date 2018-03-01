#pragma once

#include <stdint.h>
#include "wakaama/liblwm2m.h"

#ifdef __cplusplus
extern "C" {
#endif

void print_status(uint8_t status);

void prv_print_error(uint8_t status);

char * prv_dump_binding(lwm2m_binding_t binding);

void prv_dump_client(lwm2m_client_t * targetP);

// List registered clients
void prv_output_clients(char * buffer, void * user_data);

// For lwm2m_dm_ methods.
void prv_result_callback(uint16_t clientID,
                                lwm2m_uri_t * uriP,
                                int status,
                                lwm2m_media_type_t format,
                                uint8_t * data,
                                int dataLength,
                                void * userData);


// For lwm2m_observe(lwm2mH, clientId, &uri, prv_notify_callback, NULL);
void prv_notify_callback(uint16_t clientID,
                                lwm2m_uri_t * uriP,
                                int count,
                                lwm2m_media_type_t format,
                                uint8_t * data,
                                int dataLength,
                                void * userData);

#ifdef __cplusplus
}
#endif
