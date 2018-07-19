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
#include "lwm2m/server.h"
#include "../wakaama/internals.h"
#include "lwm2m/debug.h"
#include "lwm2m/network.h"
#include "network_common.h"

#if defined(LWM2M_WITH_DTLS) && defined(LWM2M_SERVER_MODE)
void lwm2m_server_dtls_psk(lwm2m_context_t * context, const char* publicId, const char* psk, unsigned short pskLen) {
    network_t* network = (network_t*) context->userData;
    if (network->secretKey) {
        lwm2m_free(network->secretKey);
        network->secretKey=NULL;
        network->secretKeyLen=0;
    }

    if (network->publicIdentity) {
        lwm2m_free(network->publicIdentity);
        network->publicIdentity=NULL;
        network->publicIdLen=0;
    }

    network->handshakeState = DTLS_NO_HANDSHAKE_IN_PROGRESS;

    // Reset all connections
    connection_t* c= network->connection_list;
    while(c){
        mbedtls_ssl_session_reset (&c->ssl);
        c = c->next;
    }

    // Reset state
    context->state = STATE_INITIAL;

    if (publicId == NULL || psk == NULL) {
        network->publicIdentity = NULL;
    } else {
        network->publicIdLen = (unsigned short)strlen(publicId);
        network->publicIdentity = lwm2m_malloc(network->publicIdLen+1);
        strcpy(network->publicIdentity, publicId);
    }

    if (psk) {
       network->secretKey = lwm2m_malloc(pskLen);
       memcpy(network->secretKey, psk, pskLen);
       network->secretKeyLen = pskLen;
    }
}
#else
void lwm2m_server_dtls_psk(lwm2m_context_t * context, const char* publicId, const char* psk, unsigned short pskLen) {
    (void)context;
    (void)publicId;
    (void)psk;
    (void)pskLen;
}
#endif
