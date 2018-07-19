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
#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

struct timeval;

/**
 * @brief Initialize wakaame in client mode.
 *
 * Initialize the given wakaame client context and the network module.
 * Close the client context with lwm2m_client_close().
 *
 * @param context Wakaama client context. May not be NULL.
 * @param endpointName The server uses this name to identify a client over multiple sessions
 * @return Return 0 if socket binding failed. Otherwise returns the number
 *     of sockets the method could bind to (for IPv4 and IPv6 each on all available interfaces).
 */
uint8_t lwm2m_client_init(lwm2m_client_context_t* context, const char * endpointName);

/**
 * @brief Close the given wakaama client context.
 *
 * Will release dynamically aquired ressources and calls lwm2m_network_close().
 * All added servers are gone after this call.
 * This will not release objects created by lwm2m_object_create.
 *
 * @param context Wakaama client context. May not be NULL.
 */
void lwm2m_client_close(lwm2m_client_context_t* context);

/**
 * Call this method periodically.
 *
 * Internally it will process new network packages as well as progress in the wakaamas state machine.
 *
 * @param contextP Wakaama context
 */
void lwm2m_process(lwm2m_context_t * contextP);

/**
 * Return the state machines state.
 *
 * @param contextP Wakaama context
 */
lwm2m_client_state_t lwm2m_state(lwm2m_context_t * contextP);
/**
 * Watch server connections and reset the lwm2m state machine to force reconnects,
 * if the current state is STATE_BOOTSTRAP_REQUIRED.
 *
 * @param reconnectTime Reconnect time in seconds
 */
void lwm2m_watch_and_reconnect(lwm2m_context_t * contextP, int reconnectTime);

/**
 * Adds a new server to the lwm2m client. The client statemachine will try to connect to this
 * server with the next iteration (usually caused by calling lwm2m_process(next_event)).
 *
 * Hint: If you want to connect via a dtls secured connection, pass a "coaps://" URI. You need
 * to also call lwm2m_add_server(...) for instance to add the preshared key information.
 *
 * @param contextP Wakaama context
 * @param shortServerID A unique server id
 * @param uri The server URI
 * @param lifetime A lifetime in seconds
 * @param storing If notifications should be stored and resend if a server connection was interruppted and then reconnected.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
bool lwm2m_add_server(lwm2m_context_t *contextP, uint16_t shortServerID,
                             const char* uri, uint32_t lifetime, bool storing);

/**
 * Alters a servers security details by adding preshared key DTLS information.
 * Call this before entering the main loop (lwm2m_process(context)).
 *
 * Warning: If you have specified a "coap://" URI in lwm2m_add_server(...), then
 * publicId and psk will be set to NULL on a connection attempt.
 *
 * The LwM2M specification V1.0 says: "Since the security of the default PSK Cipher Suites
 * rely on the length and the entropy of this shared secret
 * it is RECOMMENDED to provision a 16 byte (128 bit) key"
 *
 * @param contextP Wakaama context
 * @param shortServerID A unique server id
 * @param publicId publicIdentity for DTLS. May be NULL if no secure connection is used.
 * The expected c-string is copied to a new memory location.
 * @param psk Passkey if DTLS is used. May be NULL. The byte array is copied to a new memory location.
 * @param pskLen Passkey length. Should be 0 if no passkey is used.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
bool lwm2m_use_dtls_psk(lwm2m_context_t *contextP, uint16_t shortServerID, const char* publicId,
                        const char* psk, unsigned short pskLen);


/**
 * Alters a servers security details by adding a raw public key of the server in question.
 * Call this before entering the main loop (lwm2m_process(context)).
 *
 * Warning: If you have specified a "coap://" URI in lwm2m_add_server(...), then
 * the public key will be set to NULL on a connection attempt.
 *
 * @param contextP Wakaama context
 * @param shortServerID A unique server id
 * @param serverPublicKey The public key MUST be encoded as
 * ASN.1 DER SubjectPublicKeyInfo defined in [RFC7250]. Will be copied to a new memory location.
 * @param clientPrivateKey The private key MUST be encoded as
 * ASN.1 DER OneAsymmetricKey defined in [RFC5958]. Will be copied to a new memory location.
 * @param clientPublicKey Must be NULL for now.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
//bool lwm2m_use_dtls_public_raw_key(lwm2m_context_t *contextP, uint16_t shortServerID,
//                               const char* serverPublicKey, unsigned short serverPublicKeyLen,
//                               const char* clientPrivateKey, unsigned short clientPrivateKeyLen,
//                               const char* clientPublicKey, unsigned short clientPublicKeyLen);

/**
 * Alters a servers security details by adding certificate DTLS information. Call this before entering the
 * main loop (lwm2m_process(context)).
 *
 * Hint: If you have specified a "coap://" URI in lwm2m_add_server(...), then
 * the certificate will not be used.
 *
 * @param contextP Wakaama context
 * @param shortServerID A unique server id
 * @param certificates X.509v3 Certificate for DTLS.
 * It MUST be the DER encoded binary format, as defined in [RFC5280]. Will be copied to a new memory location.
 * @param certificatesLen Certificates length
 * @param clientPrivateKey The private key MUST be encoded as
 * ASN.1 DER OneAsymmetricKey defined in [RFC5958]. Will be copied to a new memory location.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
//bool lwm2m_use_dtls_certificate(lwm2m_context_t *contextP, uint16_t shortServerID,
//      const char* certificates, unsigned short certificatesLen,
//      const char* clientPrivateKey, unsigned short clientPrivateKeyLen);

/**
 * Informs the lwm2m server about a disconnect and flags the connection as disconnected.
 * Disconnected servers are still available until `lwm2m_remove_unregistered_servers` is called.
 *
 * @param contextP Wakaama context
 * @param security_instance_id The security instance id which refers to a specific server
 */
bool lwm2m_unregister_server(lwm2m_context_t *contextP, uint16_t security_instance_id);

/**
 * Removes all unregistered server, by removing all related security objects.
 * Puts the client back to STATE_INITIAL if the server list has been altered.
 *
 * @param contextP Wakaama context
 */
void lwm2m_remove_unregistered_servers(lwm2m_context_t *contextP);

/**
 * Returns the uri of a server.
 *
 * The c-string is not copied and valid as long as the respective security object is alive.
 *
 * @param contextP Wakaama context
 * @param security_instance_id The security instance id which refers to a specific server
 */
const char* lwm2m_get_server_uri(lwm2m_context_t *contextP, uint16_t shortServerID);

/**
 * @brief Return true if wakaama is connected to a lwm2m server.
 *
 * @param contextP Wakaama context
 */
bool lwm2m_is_connected(lwm2m_context_t *contextP);

#ifdef __cplusplus
}
#endif
