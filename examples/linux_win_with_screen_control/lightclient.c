#include "wakaama_simple_client.h"
#include "wakaama_object_utils.h"
#include "wakaama_client_debug.h"
#include "wakaama_network.h"
#include "test_object.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

static int g_quit = 0;

void handle_sigint(int signum)
{
    printf("Wait for socket timeout...\n");
    g_quit = 1;
}

int main(int argc, char *argv[])
{
    /*
     * We catch Ctrl-C signal for a clean exit
     */
    signal(SIGINT, handle_sigint);

    device_instance_t * device_data = lwm2m_device_data_get();
    device_data->manufacturer = "test manufacturer";
    device_data->model_name = "test model";
    device_data->device_type = "sensor";
    device_data->firmware_ver = "1.0";
    device_data->serial_number = "140234-645235-12353";
    lwm2m_context_t * lwm2mH = lwm2m_client_init("testClient");
    if (lwm2mH == 0)
    {
        fprintf(stderr, "Failed to initialize wakaama\r\n");
        return -1;
    }

    // Create object
    lwm2m_object_t* test_object = lwm2m_object_create(1024, true, test_object_get_meta());
    lwm2m_object_instance_add(test_object, test_object_create_instance(10));
    test_object->executeFunc = test_object_execute_cb;
    lwm2m_add_object(lwm2mH, test_object);

    uint8_t bound_sockets = lwm2m_network_init(lwm2mH, NULL);

    if (bound_sockets == 0)
    {
        fprintf(stderr, "Failed to open socket: %d %s\r\n", errno, strerror(errno));
        return -1;
    }

    /*
     * We now enter a while loop that will handle the communications from the server
     */
    while (0 == g_quit)
    {
        struct timeval tv = {5,0};
        fd_set readfds = {0};
        for (uint8_t c = 0; c < bound_sockets; ++c)
            FD_SET(lwm2m_network_native_sock(lwm2mH, c), &readfds);

        print_state(lwm2mH);

        uint8_t result = lwm2m_step(lwm2mH, &tv.tv_sec);
        if (result != 0)
        {
            fprintf(stderr, "lwm2m_step() failed: 0x%X\r\n", result);
        }

        /*
         * This part wait for an event on the socket until "tv" timed out (set
         * with the precedent function)
         */
        result = select(FD_SETSIZE, &readfds, NULL, NULL, &tv);

        if (result < 0 && errno != EINTR)
        {
            fprintf(stderr, "Error in select(): %d %s\r\n", errno, strerror(errno));
        }

        for (uint8_t c = 0; c < bound_sockets; ++c)
        {
            if (result > 0 && FD_ISSET(lwm2m_network_native_sock(lwm2mH, c), &readfds))
            {
                lwm2m_network_process(lwm2mH);
            }
        }
    }

    printf("finished\n");

    lwm2m_network_close(lwm2mH);
    lwm2m_client_close();

    lwm2m_object_free(test_object);

    return 0;
}
