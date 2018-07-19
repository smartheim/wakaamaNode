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
#include "../../internal_objects.h"

#define COAP_505_NO_NETWORK_CONNECTION      (uint8_t)0xA5
#define COAP_506_DTLS_CONNECTION_DENIED     (uint8_t)0xA6
#define COAP_299_DTLS_HANDSHAKE_IN_PROGRESS (uint8_t)0x6A

#ifdef __cplusplus
extern "C" {
#endif

/**
  * The lwm2m client context. Need to be initalized with lwm2m_client_init()
  * and closed with lwm2m_client_close().
  * Use CTX(client_context) to get a pointer to the `lwm2m_context_t` for most of the APIs.
  */
typedef struct _lwm2m_client_context_t_ {
    lwm2m_context_t context;
    lwm2m_object_t securityObject;
    server_object_t serverObject;
    device_object_t deviceObject;
    device_instance_t deviceInstance;
} lwm2m_client_context_t;

#define CTX(completeContext) (&((completeContext).context))

#ifdef __cplusplus
}
#endif
