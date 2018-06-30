#include "lwm2m/debug.h"
#include "wakaama_config.h"
#include "wakaama/liblwm2m.h"
#include "wakaama/internals.h"

void print_state(lwm2m_context_t * lwm2mH)
{
    lwm2m_printf("State: ");
    switch(lwm2mH->state)
    {
    case STATE_INITIAL:
        lwm2m_printf("STATE_INITIAL");
        break;
    case STATE_BOOTSTRAP_REQUIRED:
        lwm2m_printf("STATE_BOOTSTRAP_REQUIRED");
        break;
    case STATE_BOOTSTRAPPING:
        lwm2m_printf("STATE_BOOTSTRAPPING");
        break;
    case STATE_REGISTER_REQUIRED:
        lwm2m_printf("STATE_REGISTER_REQUIRED");
        break;
    case STATE_REGISTER_REQUIRED2:
        lwm2m_printf("STATE_REGISTER_REQUIRED2");
        break;
    case STATE_REGISTERING:
        lwm2m_printf("STATE_REGISTERING");
        break;
    case STATE_READY:
        lwm2m_printf("STATE_READY");
        break;
    }
    lwm2m_printf("\r\n");

    lwm2m_server_t * targetP;

    if (lwm2mH->bootstrapServerList == NULL)
    {
        lwm2m_printf("No Bootstrap Server.\r\n");
    }
    else
    {
        lwm2m_printf("Bootstrap Servers:\r\n");
        for (targetP = lwm2mH->bootstrapServerList ; targetP != NULL ; targetP = targetP->next)
        {
            lwm2m_printf(" - Security Object ID %d", targetP->secObjInstID);
            lwm2m_printf("\tHold Off Time: %lu s", (unsigned long)targetP->lifetime);
            lwm2m_printf("\tstatus: ");
            switch(targetP->status)
            {
            case STATE_DEREGISTERED:
                lwm2m_printf("DEREGISTERED\r\n");
                break;
            case STATE_BS_HOLD_OFF:
                lwm2m_printf("CLIENT HOLD OFF\r\n");
                break;
            case STATE_BS_INITIATED:
                lwm2m_printf("BOOTSTRAP INITIATED\r\n");
                break;
            case STATE_BS_PENDING:
                lwm2m_printf("BOOTSTRAP PENDING\r\n");
                break;
            case STATE_BS_FINISHED:
                lwm2m_printf("BOOTSTRAP FINISHED\r\n");
                break;
            case STATE_BS_FAILED:
                lwm2m_printf("BOOTSTRAP FAILED\r\n");
                break;
            default:
                lwm2m_printf("INVALID (%d)\r\n", (int)targetP->status);
            }
            lwm2m_printf("\r\n");
        }
    }

    if (lwm2mH->serverList == NULL)
    {
        lwm2m_printf("No LWM2M Server.\r\n");
    }
    else
    {
        lwm2m_printf("LWM2M Servers:\r\n");
        for (targetP = lwm2mH->serverList ; targetP != NULL ; targetP = targetP->next)
        {
            lwm2m_printf(" - Server ID %d", targetP->shortID);
            lwm2m_printf("\tstatus: ");
            switch(targetP->status)
            {
            case STATE_DEREGISTERED:
                lwm2m_printf("DEREGISTERED\r\n");
                break;
            case STATE_REG_PENDING:
                lwm2m_printf("REGISTRATION PENDING\r\n");
                break;
            case STATE_REGISTERED:
                lwm2m_printf("REGISTERED\tlocation: \"%s\"\tLifetime: %lus\r\n", targetP->location, (unsigned long)targetP->lifetime);
                break;
            case STATE_REG_UPDATE_PENDING:
                lwm2m_printf("REGISTRATION UPDATE PENDING\r\n");
                break;
            case STATE_DEREG_PENDING:
                lwm2m_printf("DEREGISTRATION PENDING\r\n");
                break;
            case STATE_REG_FAILED:
                lwm2m_printf("REGISTRATION FAILED\r\n");
                break;
            default:
                lwm2m_printf("INVALID (%d)\r\n", (int)targetP->status);
            }
            lwm2m_printf("\r\n");
        }
    }
}

