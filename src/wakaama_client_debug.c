#include "wakaama/liblwm2m.h"
#include "wakaama/internals.h"

void print_state(lwm2m_context_t * lwm2mH)
{
    lwm2m_server_t * targetP;

    LOG("State: ");
    switch(lwm2mH->state)
    {
    case STATE_INITIAL:
        LOG("STATE_INITIAL");
        break;
    case STATE_BOOTSTRAP_REQUIRED:
        LOG("STATE_BOOTSTRAP_REQUIRED");
        break;
    case STATE_BOOTSTRAPPING:
        LOG("STATE_BOOTSTRAPPING");
        break;
    case STATE_REGISTER_REQUIRED:
        LOG("STATE_REGISTER_REQUIRED");
        break;
    case STATE_REGISTERING:
        LOG("STATE_REGISTERING");
        break;
    case STATE_READY:
        LOG("STATE_READY");
        break;
    default:
        LOG("Unknown !");
        break;
    }
    LOG("\r\n");

    targetP = lwm2mH->bootstrapServerList;

    if (lwm2mH->bootstrapServerList == NULL)
    {
        LOG("No Bootstrap Server.\r\n");
    }
    else
    {
        LOG("Bootstrap Servers:\r\n");
        for (targetP = lwm2mH->bootstrapServerList ; targetP != NULL ; targetP = targetP->next)
        {
            LOG_ARG(" - Security Object ID %d", targetP->secObjInstID);
            LOG_ARG("\tHold Off Time: %lu s", (unsigned long)targetP->lifetime);
            LOG("\tstatus: ");
            switch(targetP->status)
            {
            case STATE_DEREGISTERED:
                LOG("DEREGISTERED\r\n");
                break;
            case STATE_BS_HOLD_OFF:
                LOG("CLIENT HOLD OFF\r\n");
                break;
            case STATE_BS_INITIATED:
                LOG("BOOTSTRAP INITIATED\r\n");
                break;
            case STATE_BS_PENDING:
                LOG("BOOTSTRAP PENDING\r\n");
                break;
            case STATE_BS_FINISHED:
                LOG("BOOTSTRAP FINISHED\r\n");
                break;
            case STATE_BS_FAILED:
                LOG("BOOTSTRAP FAILED\r\n");
                break;
            default:
                LOG_ARG("INVALID (%d)\r\n", (int)targetP->status);
            }
            LOG("\r\n");
        }
    }

    if (lwm2mH->serverList == NULL)
    {
        LOG("No LWM2M Server.\r\n");
    }
    else
    {
        LOG("LWM2M Servers:\r\n");
        for (targetP = lwm2mH->serverList ; targetP != NULL ; targetP = targetP->next)
        {
            LOG_ARG(" - Server ID %d", targetP->shortID);
            LOG("\tstatus: ");
            switch(targetP->status)
            {
            case STATE_DEREGISTERED:
                LOG("DEREGISTERED\r\n");
                break;
            case STATE_REG_PENDING:
                LOG("REGISTRATION PENDING\r\n");
                break;
            case STATE_REGISTERED:
                LOG_ARG("REGISTERED\tlocation: \"%s\"\tLifetime: %lus\r\n", targetP->location, (unsigned long)targetP->lifetime);
                break;
            case STATE_REG_UPDATE_PENDING:
                LOG("REGISTRATION UPDATE PENDING\r\n");
                break;
            case STATE_DEREG_PENDING:
                LOG("DEREGISTRATION PENDING\r\n");
                break;
            case STATE_REG_FAILED:
                LOG("REGISTRATION FAILED\r\n");
                break;
            default:
                LOG_ARG("INVALID (%d)\r\n", (int)targetP->status);
            }
            LOG("\r\n");
        }
    }
}

