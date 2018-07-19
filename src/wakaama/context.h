#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "config.h"
#include "bootstrap.h"
#include "server_object.h"
#include "objects.h"
#include "observe.h"
#include "transaction.h"
#include "server_clientlist.h"
#include "errorcodes.h"

#ifdef LWM2M_CLIENT_MODE

typedef enum
{
    STATE_INITIAL = 0,
    STATE_BOOTSTRAP_REQUIRED,
    STATE_BOOTSTRAPPING,
    STATE_REGISTER_REQUIRED,
    STATE_REGISTER_REQUIRED2,
    STATE_REGISTERING,
    STATE_READY,
    STATE_EXCEPTIONAL
} lwm2m_client_state_t;

#endif

typedef struct _lwm2m_context_t lwm2m_context_t;

struct _lwm2m_context_t
{
#ifdef LWM2M_CLIENT_MODE
    lwm2m_client_state_t state;
    lwm2m_error_codes_t  lastStepError;
    char *               endpointName;
    char *               msisdn;
    char *               altPath;
    lwm2m_server_t *     bootstrapServerList;
    lwm2m_server_t *     serverList;
    lwm2m_object_t *     objectList;
    lwm2m_observed_t *   observedList;
#endif
#ifdef LWM2M_SERVER_MODE
    lwm2m_client_t *        clientList;
    lwm2m_result_callback_t monitorCallback;
    void *                  monitorUserData;
#endif
#ifdef LWM2M_BOOTSTRAP_SERVER_MODE
    lwm2m_bootstrap_callback_t bootstrapCallback;
    void *                     bootstrapUserData;
#endif
    uint16_t                nextMID;
    lwm2m_transaction_t *   transactionList;
    void *                  userData;
};


// initialize a liblwm2m context.
lwm2m_context_t * lwm2m_init(void * userData);
// close a liblwm2m context.
void lwm2m_close(lwm2m_context_t * contextP);

// perform any required pending operation and adjust timeoutP to the maximal time interval to wait in seconds.
void lwm2m_step(lwm2m_context_t * contextP, time_t * timeoutP);
