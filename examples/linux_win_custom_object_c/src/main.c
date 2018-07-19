/*****
 Linux/Windows C-API Example with custom object 1024 to switch screens on/off via lwm2m.
 To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
*****/

#include "lwm2m/c_connect.h"
#include "lwm2m/c_objects.h"
#include "lwm2m/debug.h"
#include "lwm2m/network.h"
#include "custom_object.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>

static volatile int g_quit = 0;

void handle_sigint(int signum) {
    (void)signum;
    printf("Wait for socket timeout...\n");
    g_quit = 1;
}

int main()
{
    /*
     * We catch Ctrl-C signal for a clean exit
     */
    signal(SIGINT, handle_sigint);

    lwm2m_client_context_t context;

    context.deviceInstance.manufacturer = "test manufacturer";
    context.deviceInstance.model_name = "test model";
    context.deviceInstance.device_type = "linux app";
    context.deviceInstance.firmware_ver = "1.0";
    context.deviceInstance.serial_number = "140234-645235-12353";

    // Create object with the C-Object API
    lwm2m_object_t* test_object = get_screen_object();
    lwm2m_add_initialize_object(CTX(context), test_object, false);
    lwm2m_object_instance_add(CTX(context), test_object, get_an_instance());

    uint8_t bound_sockets = lwm2m_client_init (&context, "testClient");

    if (bound_sockets == 0)
    {
        fprintf(stderr, "Failed to open socket: %d %s\r\n", errno, strerror(errno));
        return -1;
    }
    
    // Connect to the lwm2m server with unique id 123, lifetime of 100s, no storing of
    // unsend messages. The host url is either coap:// or coaps://.
    assert(lwm2m_add_server(CTX(context), 123, "coap://leshan.eclipse.org", 100, false));
    
    // If you want to establish a DTLS secured connection, you need to alter the security
    // information:
    #ifdef LWM2M_WITH_DTLS
    lwm2m_use_dtls_psk(CTX(context), 123, "publicid", "password", sizeof("password"));
    #endif

    struct timeval tv = {0,0};
    fd_set readfds = {0};

    /* We now enter a while loop that will handle the communications from the server */
    while (0 == g_quit)
    {
        memset(&readfds,sizeof(fd_set),0);
        for (uint8_t c = 0; c < bound_sockets; ++c)
            FD_SET(lwm2m_network_native_sock(CTX(context), c), &readfds);

        /* This part wait for an event on the socket until "tv" timed out */
        int result = select(FD_SETSIZE, &readfds, NULL, NULL, &tv);

        if (result < 0 && errno != EINTR) {
            fprintf(stderr, "Error in select(): %d %s\r\n", errno, strerror(errno));
        }

        // Sleep 20sec before doing another main loop run if no packet has been received
        // and lwm2m_process or lwm2m_watch_and_reconnect has no earlier due time.
        tv.tv_sec = 20;
        result = lwm2m_process(CTX(context));
        if (result == COAP_503_SERVICE_UNAVAILABLE)
            printf("No server added! Call lwm2m_add_server()\n");
        else if (result == COAP_505_NO_NETWORK_CONNECTION)
            fprintf(stderr, "No sockets open. Reinit the network\n");
        else if (result == COAP_506_DTLS_CONNECTION_DENIED)
            fprintf(stderr, "DTLS connection denied. Server may not know PSK for client %s\n", CTX(context)->endpointName);
        else if (result != 0)
            fprintf(stderr, "lwm2m_step() failed: 0x%X\n", result);
        lwm2m_watch_and_reconnect(CTX(context),5);
    }

    printf("finished\n");

    lwm2m_remove_object(CTX(context), test_object->objID);
    lwm2m_client_close(&context);

    return 0;
}
