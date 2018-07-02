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

#include <stdint.h>
#include "../src/wakaama/liblwm2m.h"

#ifdef __cplusplus
extern "C" {
#endif

void print_status(int status);

void prv_print_error(int status);

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
