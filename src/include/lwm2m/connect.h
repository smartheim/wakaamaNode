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
#include "../../wakaama/liblwm2m.h"
#include "object_device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize wakaame in client mode.
 * Will allocate objects and initializes them.
 * This method can only be called once! Close the client context with lwm2m_client_close().
 * @param endpointName
 * @return A wakaama context.
 */
lwm2m_context_t * lwm2m_client_init(const char * endpointName);

/**
 * Call this method periodically.
 *
 * @param timeoutInSec Returns a time_t value that tells you when the next call is due.
 * Does not modify time_t if it already has a value that is sooner than the next due time.
 * @return Returns a wakaama error code.
 */
int lwm2m_client_process(time_t* timeoutInSec);

/**
 * @brief Return the context created by lwm2m_client_init().
 * @return A wakaama context.
 */
lwm2m_context_t * lwm2m_client_get_context(void);

/**
 * @brief Close the given wakaama client context,
 * release dynamically aquired ressources and calls lwm2m_network_close().
 * All added servers are gone after this call.
 * This will not release objects created by lwm2m_object_create.
 */
void lwm2m_client_close(void);

/**
 * Adds a new server to the lwm2m client. The client statemachine will try to connect to this
 * server with the next iteration (usually caused by calling lwm2m_network_process(context)).
 *
 * @param shortServerID A unique server id
 * @param uri The server URI
 * @param lifetime A lifetime in seconds
 * @param storing If notifications should be stored and resend if a server connection was interruppted and then reconnected.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
bool lwm2m_add_server(uint16_t shortServerID, const char* uri, uint32_t lifetime, bool storing);

/**
 * Alters a servers security details by adding preshared key DTLS information. Call this before entering the
 * main loop (lwm2m_network_process(context)).
 *
 * @param shortServerID A unique server id
 * @param publicId publicIdentity for DTLS. May be NULL if no secure connection is used.
 * The expected c-string is copied to a new memory location.
 * @param psk Passkey if DTLS is used. May be NULL. The byte array is copied to a new memory location.
 * @param pskLen Passkey length. Should be 0 if no passkey is used.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
bool lwm2m_security_use_preshared(uint16_t shortServerID, const char* publicId, const char* psk, unsigned short pskLen);

/**
 * Alters a servers security details by adding certificate DTLS information. Call this before entering the
 * main loop (lwm2m_network_process(context)).
 *
 * @param shortServerID A unique server id
 * @param certificates Certificates for DTLS.
 * @param certificatesLen Certificates length
 * @return Return true if successfully added and false if aborted due to no memory.
 */
//bool lwm2m_security_use_certificate(uint16_t shortServerID, const char* certificates, unsigned short certificatesLen);

/**
 * Unregisteres from a connected server.
 * @param security_instance_id The security instance id which refers to a specific server
 */
bool lwm2m_unregister_server(uint16_t security_instance_id);

/**
 * Removes all unregistered server, by removing all related security objects.
 * Puts the client back to STATE_INITIAL if the server list has been altered.
 */
void lwm2m_remove_unregistered_servers(void);

/**
 * Returns the uri of a server.
 *
 * @param security_instance_id The security instance id which refers to a specific server
 * @param uriBuffer The destination buffer
 * @param buffer_len The destination buffer length
 */
const char* lwm2m_get_server_uri(uint16_t shortServerID);

/**
 * @brief Return true if wakaama is connected to a lwm2m server.
 * @return
 */
bool lwm2m_is_connected(void);

#ifdef __cplusplus
}
#endif
