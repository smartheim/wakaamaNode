/*****
 Linux/Windows C-API Example with custom object 1024 to switch screens on/off via lwm2m.
 To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
*****/

#include "lwm2m/connect.h"
#include "lwm2m/objects.h"
#include "lwm2m/debug.h"
#include "lwm2m/network.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <signal.h>

#include <cstdlib>
#include <vector>
#include <chrono>

#ifdef WIN32
#include <windows.h>
#else
#include <getopt.h>
#endif

// For c++ projects with firmware support
#include "lwm2m/firmware.h"

#include "lwm2mObjects/3312.h"

namespace {
    volatile int g_quit = 0;
}

void switchMontitors(bool power){
    std::string d = std::getenv ("XDG_CURRENT_DESKTOP");
    if (d=="GNOME") {
        // Use DBUS and talk to Mutter, the screen compositor
        if (power)
            system("busctl --user set-property org.gnome.Mutter.DisplayConfig /org/gnome/Mutter/DisplayConfig org.gnome.Mutter.DisplayConfig PowerSaveMode i 0");
        else
            system("busctl --user set-property org.gnome.Mutter.DisplayConfig /org/gnome/Mutter/DisplayConfig org.gnome.Mutter.DisplayConfig PowerSaveMode i 1");
    } else {
        #ifdef __linux__
        if (power)
            system("xset dpms force on");
        else
            system("xset dpms force standby");
        #elif defined(WIN32)
        if (power) {
            // Emulate a mouse move to turn monitors on again
            INPUT input = { INPUT_MOUSE };
            input.mi.dwFlags = MOUSEEVENTF_MOVE;
            SendInput(1, &input, sizeof(INPUT));
        } else
            SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
        #else
            #error "System not supported"
        #endif
    }
}

void handle_sigint(int signum) {
    (void)signum;
    printf("Wait for socket timeout...\n");
    g_quit = 1;
}

int main(int argc, char *argv[])
{
    // Scan arguments
    std::string host("coaps://leshan.eclipse.org");
    std::string endpoint = "screenControl";
    std::string psk_publicIdentity = "publicid";
    std::string psk_key = "password";
    long timeout = 0;

    // We need a different endpoint for an unsecured client,
    // cause the server will compare endpoints and expects a dtls connection.
    if (host.compare (0,5,"coap:")==0) endpoint+="Unsecure";

    int opt;
    while ((opt = getopt(argc, argv, "e:h:i:p:t:")) != -1) {
        switch (opt) {
        case 't':
            timeout = atoi(optarg);
            break;
        case 'i':
            psk_publicIdentity = optarg;
            break;
        case 'p':
            psk_key = optarg;
            break;
        case 'e':
            endpoint = optarg;
            break;
        case 'h':
            host = optarg;
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-h lwm2m_server_address (coap://leshan.eclipse.org)] "
                    "[-e endpoint (screenControl)] [-p psk_key (\"password\")] "
                    "[-i psk_identity (\"publicid\")] [-t timeout_in_sec]"
                    "\n\tUse a coaps address for a dtls connection."
                    "\n\tA timeout in seconds will quit the program after that time. Returns 0 if connected to a server successfully.\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    LwM2MConnect lwm2m(endpoint.c_str ());
    FirmwareUpdate firmwareUpdate("1.0", UPDATE_PROTOCOL_COAP);
    KnownObjects::id3312::object screenObject;
    KnownObjects::id3312::instance screenInstance;

    /* We catch Ctrl-C signal for a clean exit */
    signal(SIGINT, handle_sigint);
    
    lwm2m.deviceInstance.manufacturer = "test manufacturer";
    lwm2m.deviceInstance.model_name = "test model";
    lwm2m.deviceInstance.device_type = "linux app";
    lwm2m.deviceInstance.firmware_ver = "1.0";
    lwm2m.deviceInstance.serial_number = "140234-645235-12353";

    // Check for new firmware binary
    firmwareUpdate.checkIsUpdated(argc, argv);

    // Create object with the C++-Object API
    uint8_t bound_sockets = lwm2m.socket_count();
    if (bound_sockets == 0) {
        fprintf(stderr, "Failed to open socket: %d %s\r\n", errno, strerror(errno));
        return -1;
    }

    // React on object instance changes
    screenObject.verifyWrite=[](KnownObjects::id3312::instance* instance, uint16_t res){
        if (res==KnownObjects::id3312::RESID::OnOff)
            switchMontitors(instance->OnOff);
        return true;
    };

    // Add instance to object and object to lwm2m library
    screenObject.addInstance (CTX(lwm2m),&screenInstance);
    screenObject.registerObject (CTX(lwm2m),false);

    // Connect to the lwm2m server with unique id 123, lifetime of 100s, no storing of
    // unsend messages. The host url is either coap:// or coaps://.
    lwm2m.add_server (123, host.c_str (), 100, false);
    
    // If you want to establish a DTLS secured connection, you need to alter the security
    // information:
    #ifdef LWM2M_WITH_DTLS
    lwm2m.use_dtls_psk(123, psk_publicIdentity.c_str(), psk_key.c_str (), (unsigned short)psk_key.size ());
    #endif

    int result = 0;
    auto start = std::chrono::system_clock::now()+std::chrono::seconds(timeout);

    /* We now enter the programs main loop. Abort condition is the g_quit flag (press CTRL+C). */
    while (0 == g_quit){
        struct timeval next_event = {20,0};
        result = lwm2m.process(&next_event);
        lwm2m.watch_and_reconnect(&next_event, 5);
        if (result!=COAP_NO_ERROR){
            print_state (CTX(lwm2m));
        } else {
            print_state (CTX(lwm2m));
        }
        lwm2m.block_wait(next_event);
        if (timeout){
            const std::chrono::duration<double> d = std::chrono::system_clock::now()-start;
            if (d.count ()>0.0) {
                break;
            }
        }
    }


    screenObject.unregisterObject(CTX(lwm2m));

    printf("finished: %i\n", result);
    return result;
}
