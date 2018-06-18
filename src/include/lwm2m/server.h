/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 * 
 * Although this library is not build for lwm2m servers, some APIs for servers are required as well for performing the test suits.
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
#include "../../wakaama/liblwm2m.h"
#include "object_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sets the preshared key for server dtls connections.
 * 
 * If this method is called, the given wakaama network context will switch to DTLS if publicID and psk are not NULL.
 * Client connections that are not using DTLS, cannot be accepted anymore if in DTLS mode. 
 * 
 * @param context A wakaama context.
 * @param publicId publicIdentity for DTLS. May be NULL if no secure connection is used.
 * The expected c-string is copied to a new memory location.
 * @param psk Passkey if DTLS is used. May be NULL. The byte array is copied to a new memory location.
 * @param pskLen Passkey length. Should be 0 if no passkey is used.
 * @return 
 */
void lwm2m_server_dtls_psk(lwm2m_context_t * context, const char* publicId, const char* psk, unsigned short pskLen);

#ifdef __cplusplus
}
#endif
