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
#include "../../network_common.h"
#include "context.h"
#include <inttypes.h>

class LwM2MConnect: public lwm2m_client_context_t {
public:
    /**
     * @brief Initialize wakaame in client mode.
     *
     * Will allocate objects and initializes them. The context need to be stored, as it is required
     * for almost all Connect API calls as well as Object API calls.
     *
     * @param endpointName The server uses this name to identify a client over multiple sessions
     */
    LwM2MConnect(const char * endpointName);

    /**
     * @brief Close the given wakaama client context.
     *
     * Will release dynamically aquired ressources and calls network_close().
     * All added servers are gone after this call.
     * This will not release objects created by object_create.
     */
    ~LwM2MConnect();

    /**
     * Call this method periodically.
     *
     * Internally it will process new network packages as well as progress in the wakaamas state machine.
     *
     * @return Returns a wakaama error code (the result value of step())
     */
    void process();


    /**
     * `lwm2m_process` need to be called periodically and will provide an internal value in seconds when the next call is due.
     * This function returns a pointer to this due time value. You can modify (decrease) the value if required (`lwm2m_watch_and_reconnect`
     * and the ssl handshake code are doing this for example). This will cause `lwm2m_block_wait` to return sooner than the given timeout.
     *
     * @return A pointer to the next due time in sec
     */
    inline time_t* due_time() {return lwm2m_due_time(&this->context);}

    /**
     * @brief Blocks until new data is available on the sockets
     *
     * This is only available on systems that have an epoll API call
     * (and on Windows with an emulated epoll API) with POSIX sockets.
     *
     * Call process() after this method returned.
     *
     * @param timeout_in_sec The sleep time until the next event is due
     * @return Returns the socket number that received a message or 0 if it was a timeout. -1 on error.
     */
    int block_wait(unsigned timeout_in_sec);

    /**
     * Adds a new server to the lwm2m client. The client statemachine will try to connect to this
     * server with the next iteration (usually caused by calling client_process(next_event)).
     *
     * Remove a server by calling unregister_server(shortServerID)
     * followed by a remove_unregistered_servers().
     *
     * @param shortServerID A unique server id
     * @param uri The server URI
     * @param lifetime A lifetime in seconds
     * @param storing If notifications should be stored and resend if a server connection was interruppted and then reconnected.
     * @return Return true if successfully added and false if aborted due to no memory.
     */
    bool add_server(uint16_t shortServerID,
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
    bool use_dtls_psk(uint16_t shortServerID, const char* publicId,
                    const char* psk, unsigned short pskLen);

    /**
     * Alters a servers security details by adding a raw public key of the server in question.
     * Call this before entering the main loop (lwm2m_process(context)).
     *
     * Warning: If you have specified a "coap://" URI in lwm2m_add_server(...), then
     * the public key will be set to NULL on a connection attempt.
     *
     * @param shortServerID A unique server id
     * @param serverPublicKey The public key MUST be encoded as
     * ASN.1 DER SubjectPublicKeyInfo defined in [RFC7250]. Will be copied to a new memory location.
     * @param clientPrivateKey The private key MUST be encoded as
     * ASN.1 DER OneAsymmetricKey defined in [RFC5958]. Will be copied to a new memory location.
     * @param clientPublicKey Must be NULL for now.
     * @return Return true if successfully added and false if aborted due to no memory.
     */
    //bool use_dtls_public_raw_key(uint16_t shortServerID,
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
     * @param shortServerID A unique server id
     * @param certificates X.509v3 Certificate for DTLS.
     * It MUST be the DER encoded binary format, as defined in [RFC5280]. Will be copied to a new memory location.
     * @param certificatesLen Certificates length
     * @param clientPrivateKey The private key MUST be encoded as
     * ASN.1 DER OneAsymmetricKey defined in [RFC5958]. Will be copied to a new memory location.
     * @return Return true if successfully added and false if aborted due to no memory.
     */
    //bool use_dtls_certificate(uint16_t shortServerID,
    //      const char* certificates, unsigned short certificatesLen,
    //      const char* clientPrivateKey, unsigned short clientPrivateKeyLen);

    /**
     * Informs the lwm2m server about a disconnect and flags the connection as disconnected.
     * Disconnected servers are still available until `remove_unregistered_servers` is called.
     *
     * @param security_instance_id The security instance id which refers to a specific server
     */
    bool unregister_server(uint16_t security_instance_id);

    /**
     * Removes all unregistered server, by removing all related security objects.
     * Puts the client back to STATE_INITIAL if the server list has been altered.
     */
    void remove_unregistered_servers();

    /**
     * Returns the uri of a server.
     *
     * The c-string is not copied and valid as long as the respective security object is alive.
     *
     * @param security_instance_id The security instance id which refers to a specific server
     */
    const char* get_server_uri(uint16_t shortServerID);

    /**
     * @brief Return true if wakaama is connected to a lwm2m server.
     */
    bool is_connected();

    /**
     * Return how many sockets have been successfully created by the constructor.
     * If 0 is returned, the network layer was unable to create any sockets on the system
     * and this connection object is basically useless.
     */
    int socket_count();
};
