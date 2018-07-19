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
#include "lwm2m/c_connect.h"
#include "wakaama/internals.h"
#include "lwm2m/debug.h"
#include "lwm2m/network.h"
#include "network/network_common.h"

#include <stdlib.h>
#include <sys/time.h>

void lwm2m_client_close(lwm2m_client_context_t *context) {
    #ifdef LWM2M_WITH_DTLS
    // Destructor for securityObj instances
    {
        security_instance_t* s = (security_instance_t*)context->securityObject.instanceList;
        while (s) {
            lwm2m_free(s->publicIdentity);
            lwm2m_free(s->serverPublicKey);
            lwm2m_free(s->secretKey);
            s = s->next;
        }
    }
    #endif
    lwm2m_list_free(context->securityObject.instanceList);
    context->securityObject.instanceList = NULL;

    lwm2m_list_free(context->serverObject.obj.instanceList);
    context->serverObject.obj.instanceList = NULL;

    // First close lwm2m (which may send an unreg coap message)
    lwm2m_close(&context->context);
    // Close the network (and dtls session)
    lwm2m_network_close(&context->context);

    context = NULL;
}

inline security_instance_t* lwm2m_get_security_object(lwm2m_context_t *contextP, uint16_t security_instance_id){
    return (security_instance_t *)LWM2M_LIST_FIND(contextP->objectList->instanceList, security_instance_id);
}

inline static security_instance_t* get_security_object_by_server_id(lwm2m_context_t *contextP, uint16_t shortServerID) {
    security_instance_t * securityInstance=(security_instance_t *)contextP->objectList->instanceList;
    while (NULL != securityInstance) {
        if(securityInstance->shortID == shortServerID) return securityInstance;
        securityInstance = securityInstance->next;
    }
    return NULL;
}

const char* lwm2m_get_server_uri(lwm2m_context_t *contextP, uint16_t shortServerID) {
    security_instance_t * securityInstance = get_security_object_by_server_id(contextP, shortServerID);
    if (securityInstance == NULL) return NULL;
    return securityInstance->uri;
}

bool lwm2m_unregister_server(lwm2m_context_t *contextP, uint16_t security_instance_id) {
    lwm2m_server_t * serverListEntry;
    serverListEntry = (lwm2m_server_t *)LWM2M_LIST_FIND(contextP->serverList, security_instance_id);
    if (serverListEntry != NULL)
    {
        registration_deregister(contextP, serverListEntry);
        serverListEntry->dirty = true;
        return true;
    }
    return false;
    //contextP->state = STATE_INITIAL;
}

void lwm2m_remove_unregistered_servers(lwm2m_context_t *contextP) {
    lwm2m_object_t * securityObjP = contextP->objectList;
    lwm2m_object_t * serverObjP = securityObjP->next;

    lwm2m_server_t * serverListEntry = contextP->serverList;

    bool removedServers = false;
    while (serverListEntry != NULL)
    {
        if (serverListEntry->status != STATE_DEREGISTERED) {
            serverListEntry = serverListEntry->next;
            continue;
        }

        serverListEntry->dirty = true;

        uint16_t security_instance_id = serverListEntry->secObjInstID;

        security_instance_t * securityInstance;
        securityObjP->instanceList = LWM2M_LIST_RM(securityObjP->instanceList, security_instance_id, &securityInstance);
        if (securityInstance != NULL)
        {
            #ifdef LWM2M_WITH_DTLS
            // Destructor for securityObj instances
            if (securityInstance->secretKey) {
                lwm2m_free(securityInstance->secretKey);
                securityInstance->secretKey=NULL;
                securityInstance->secretKeyLen=0;
            }

            if (securityInstance->serverPublicKey) {
                lwm2m_free(securityInstance->serverPublicKey);
                securityInstance->serverPublicKey=NULL;
                securityInstance->serverPublicKeyLen=0;
            }

            if (securityInstance->publicIdentity) {
                lwm2m_free(securityInstance->publicIdentity);
                securityInstance->publicIdentity=NULL;
                securityInstance->publicIdLen=0;
            }
            #endif

            lwm2m_free(securityInstance);
        }

        server_instance_t * serverInstance;
        serverObjP->instanceList = LWM2M_LIST_RM(serverObjP->instanceList, security_instance_id, &serverInstance);
        if (serverInstance != NULL)
        {
            lwm2m_free(serverInstance);
        }

        removedServers = true;
        serverListEntry = serverListEntry->next;
    }

    if (removedServers)
        contextP->state = STATE_INITIAL;
}

static void performUpdateRegistration(lwm2m_context_t *contextP,lwm2m_list_t* instance) {
    server_instance_t * serverInstance = (server_instance_t *)instance;
    lwm2m_update_registration (contextP,serverInstance->shortServerId,true);
}

bool lwm2m_add_server(lwm2m_context_t *contextP, uint16_t shortServerID,
                             const char* uri, uint32_t lifetime, bool storing)
{
    lwm2m_object_t * securityObjP = contextP->objectList;
    lwm2m_object_t * serverObjP = securityObjP->next;

    security_instance_t * securityInstance = (security_instance_t *)lwm2m_malloc(sizeof(security_instance_t));
    server_instance_t * serverInstance = (server_instance_t *)lwm2m_malloc(sizeof(server_instance_t));

    if (NULL == securityInstance || serverInstance == NULL)
    {
        lwm2m_free(securityInstance);
        lwm2m_free(serverInstance);
        return false;
    }

    memset(securityInstance, 0, sizeof(security_instance_t));
    securityInstance->instanceId = lwm2m_list_newId(securityObjP->instanceList);
    strncpy(securityInstance->uri, uri, sizeof(securityInstance->uri));
    securityInstance->isBootstrap = false;
    securityInstance->shortID = shortServerID;
    securityInstance->clientHoldOffTime = 10;
    securityInstance->securityMode = LWM2M_SECURITY_MODE_NONE;

    securityObjP->instanceList = LWM2M_LIST_ADD(securityObjP->instanceList, securityInstance);

    memset(serverInstance, 0, sizeof(server_instance_t));
    serverInstance->instanceId = lwm2m_list_newId(serverObjP->instanceList);
    serverInstance->shortServerId = shortServerID;
    serverInstance->lifetime = lifetime;
    serverInstance->storing = storing;
    serverInstance->binding.data[0] = 'U';
    serverInstance->binding.data[1] = 0;
    serverInstance->regUpdate = performUpdateRegistration;
    serverObjP->instanceList = LWM2M_LIST_ADD(serverObjP->instanceList, serverInstance);

    contextP->state = STATE_INITIAL;
    return true;
}

#ifdef LWM2M_WITH_DTLS
void internal_erase_security_params(security_instance_t * securityInstance) {
    if (securityInstance->secretKey) {
        lwm2m_free(securityInstance->secretKey);
        securityInstance->secretKey=NULL;
        securityInstance->secretKeyLen=0;
    }

    if (securityInstance->publicIdentity) {
        lwm2m_free(securityInstance->publicIdentity);
        securityInstance->publicIdentity=NULL;
        securityInstance->publicIdLen=0;
    }
}

bool lwm2m_use_dtls_psk(lwm2m_context_t *contextP, uint16_t shortServerID,
                               const char* publicId, const char* psk, unsigned short pskLen) {
    security_instance_t * securityInstance=get_security_object_by_server_id(contextP, shortServerID);
    if (NULL == securityInstance) return false;

    internal_erase_security_params(securityInstance);

    if (publicId != NULL && psk != NULL) {
        securityInstance->securityMode = LWM2M_SECURITY_MODE_PRE_SHARED_KEY;
        securityInstance->publicIdLen = (unsigned short)strlen(publicId);
        securityInstance->publicIdentity = lwm2m_malloc(securityInstance->publicIdLen+1);
        strcpy(securityInstance->publicIdentity, publicId);

        securityInstance->secretKey = lwm2m_malloc(pskLen);
        memcpy(securityInstance->secretKey, psk, pskLen);
        securityInstance->secretKeyLen = pskLen;
    } else {
        securityInstance->securityMode = LWM2M_SECURITY_MODE_NONE;
    }

    return true;
}
#endif

inline bool lwm2m_is_connected(lwm2m_context_t *contextP) {
    return contextP->state == STATE_READY;
}

inline lwm2m_client_state_t lwm2m_state(lwm2m_context_t * contextP){
    return contextP->state;
}

inline void lwm2m_process(lwm2m_context_t *contextP) {
    lwm2m_network_process(contextP);

#ifdef LWM2M_WITH_DTLS
    const enum DtlsHandshakeState s = lwm2m_dtls_handshake_state(contextP);
    switch(s) {
        case DTLS_NO_HANDSHAKE_IN_PROGRESS:
            lwm2m_step(contextP, lwm2m_due_time(contextP));
        break;
        case DTLS_HANDSHAKE_TIMEOUT:
            // This is like a lwm2m registration handshake timeout
            contextP->state = STATE_BOOTSTRAP_REQUIRED;
        break;
    default:
        break;
}
#else
    lwm2m_step(contextP, lwm2m_due_time(contextP));
#endif
}

void lwm2m_watch_and_reconnect(lwm2m_context_t * contextP, int reconnectTime) {
    if (contextP->state == STATE_BOOTSTRAP_REQUIRED) {
        // next_event might need to happen earlier
        if (*lwm2m_due_time(contextP)>reconnectTime) *lwm2m_due_time(contextP) = reconnectTime;
        // main state reset
        contextP->state = STATE_INITIAL;
        // server object state reset
        lwm2m_server_t* s = contextP->serverList;
        while(s) {
            if (s->status == STATE_REG_FAILED)
                s->status = STATE_DEREGISTERED;
            s = s->next;
        }
    }
}

uint8_t lwm2m_client_init(lwm2m_client_context_t *context, const char * endpointName)
{
    memset(context, 0, sizeof(lwm2m_client_context_t));
    srand((int)lwm2m_gettime());
    context->context.nextMID = rand();

    init_security_object(context);
    init_server_object(context);
    init_device_object(context);

    lwm2m_object_t * objArray[3];
    objArray[0] = &context->securityObject;
    objArray[1] = &context->serverObject.obj;
    objArray[2] = &context->deviceObject.obj;

    /*
     * We configure the liblwm2m library with the name of the client - which shall be unique for each client -
     * the number of objects we will be passing through and the objects array
     */
    lwm2m_configure(&context->context, endpointName, NULL, NULL, 3, objArray);

    return lwm2m_network_init (&context->context,0);
}
