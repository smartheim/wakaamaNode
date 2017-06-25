#include "wakaama/liblwm2m.h"
#include "wakaama_simple_client.h" // for simple_lwm2m_printf
#include "wakaama/internals.h"

void print_state(lwm2m_context_t * lwm2mH)
{
    lwm2m_server_t * targetP;

    simple_lwm2m_printf("State: ");
    switch(lwm2mH->state)
    {
    case STATE_INITIAL:
        simple_lwm2m_printf("STATE_INITIAL");
        break;
    case STATE_BOOTSTRAP_REQUIRED:
        simple_lwm2m_printf("STATE_BOOTSTRAP_REQUIRED");
        break;
    case STATE_BOOTSTRAPPING:
        simple_lwm2m_printf("STATE_BOOTSTRAPPING");
        break;
    case STATE_REGISTER_REQUIRED:
        simple_lwm2m_printf("STATE_REGISTER_REQUIRED");
        break;
    case STATE_REGISTERING:
        simple_lwm2m_printf("STATE_REGISTERING");
        break;
    case STATE_READY:
        simple_lwm2m_printf("STATE_READY");
        break;
    default:
        simple_lwm2m_printf("Unknown !");
        break;
    }
    simple_lwm2m_printf("\r\n");

    targetP = lwm2mH->bootstrapServerList;

    if (lwm2mH->bootstrapServerList == NULL)
    {
        simple_lwm2m_printf("No Bootstrap Server.\r\n");
    }
    else
    {
        simple_lwm2m_printf("Bootstrap Servers:\r\n");
        for (targetP = lwm2mH->bootstrapServerList ; targetP != NULL ; targetP = targetP->next)
        {
            simple_lwm2m_printf(" - Security Object ID %d", targetP->secObjInstID);
            simple_lwm2m_printf("\tHold Off Time: %lu s", (unsigned long)targetP->lifetime);
            simple_lwm2m_printf("\tstatus: ");
            switch(targetP->status)
            {
            case STATE_DEREGISTERED:
                simple_lwm2m_printf("DEREGISTERED\r\n");
                break;
            case STATE_BS_HOLD_OFF:
                simple_lwm2m_printf("CLIENT HOLD OFF\r\n");
                break;
            case STATE_BS_INITIATED:
                simple_lwm2m_printf("BOOTSTRAP INITIATED\r\n");
                break;
            case STATE_BS_PENDING:
                simple_lwm2m_printf("BOOTSTRAP PENDING\r\n");
                break;
            case STATE_BS_FINISHED:
                simple_lwm2m_printf("BOOTSTRAP FINISHED\r\n");
                break;
            case STATE_BS_FAILED:
                simple_lwm2m_printf("BOOTSTRAP FAILED\r\n");
                break;
            default:
                simple_lwm2m_printf("INVALID (%d)\r\n", (int)targetP->status);
            }
            simple_lwm2m_printf("\r\n");
        }
    }

    if (lwm2mH->serverList == NULL)
    {
        simple_lwm2m_printf("No LWM2M Server.\r\n");
    }
    else
    {
        simple_lwm2m_printf("LWM2M Servers:\r\n");
        for (targetP = lwm2mH->serverList ; targetP != NULL ; targetP = targetP->next)
        {
            simple_lwm2m_printf(" - Server ID %d", targetP->shortID);
            simple_lwm2m_printf("\tstatus: ");
            switch(targetP->status)
            {
            case STATE_DEREGISTERED:
                simple_lwm2m_printf("DEREGISTERED\r\n");
                break;
            case STATE_REG_PENDING:
                simple_lwm2m_printf("REGISTRATION PENDING\r\n");
                break;
            case STATE_REGISTERED:
                simple_lwm2m_printf("REGISTERED\tlocation: \"%s\"\tLifetime: %lus\r\n", targetP->location, (unsigned long)targetP->lifetime);
                break;
            case STATE_REG_UPDATE_PENDING:
                simple_lwm2m_printf("REGISTRATION UPDATE PENDING\r\n");
                break;
            case STATE_DEREG_PENDING:
                simple_lwm2m_printf("DEREGISTRATION PENDING\r\n");
                break;
            case STATE_REG_FAILED:
                simple_lwm2m_printf("REGISTRATION FAILED\r\n");
                break;
            default:
                simple_lwm2m_printf("INVALID (%d)\r\n", (int)targetP->status);
            }
            simple_lwm2m_printf("\r\n");
        }
    }
}

