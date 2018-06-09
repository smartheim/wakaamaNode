/*****
 ESP8266 Led via lwm2m
 Blink the blue LED on the ESP-01 or the seperate red or blue led on the nodeMCU module
 This example code is in the public domain.
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
*****/

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <new>

#include <time.h>

#include <Arduino.h>

#include "lwm2m_connect.h"
#include "network.h"
#include "lwm2m_objects.hpp"

#include "lwm2mObjects/3311.h"

using namespace KnownObjects;

id3311::object lights;
id3311::instance ledsInstance;

lwm2m_context_t * client_context;
void setup() {
    std::set_new_handler([](){ESP.restart();}); // Reboot on heap memory outage
    
    device_instance_t * device_data = lwm2m_device_data_get();
    device_data->manufacturer = "test manufacturer";
    device_data->model_name = "test model";
    device_data->device_type = "led";
    device_data->firmware_ver = "1.0";
    device_data->serial_number = "140234-645235-12353";
    client_context = lwm2m_client_init("testClient");
    if (client_context == 0)
    {
        printf("Failed to initialize wakaama\n");
        return;
    }

    // Overwrite the verifyFunction and "abuse" it as value changed event.
    lights.verifyWrite = [](Lwm2mObjectInstance* instance, uint16_t res_id) {
        auto inst = instance->as<id3311::instance>();
        // Is it instance 0 and the OnOff resource?
        if (inst->id == 0 && id3311::RESID::OnOff == res_id) {
            // Change the led pin depending on the OnOff value
            digitalWrite(LED_BUILTIN, inst->OnOff);
        }
        // Return true to accept the value and ACK to the server
        return true;
    };

    ledsInstance.id = 0; // set instance id
    lights.addInstance(client_context, &ledsInstance);
    lights.registerObject(client_context, false);

    // Initialize the LED_BUILTIN pin as an output
    pinMode(LED_BUILTIN, OUTPUT);

    // Wait for network to connect

    // Init lwm2m network
    uint8_t bound_sockets = lwm2m_network_init(client_context, NULL);
    if (bound_sockets == 0)
        printf("Failed to open socket\n");
    
    // Connect to the lwm2m server with unique id 123, lifetime of 100s, no storing of
    // unsend messages. The host url is either coap:// or coaps://.
    lwm2m_add_server(123, "coap://192.168.1.18", 100, false);
    
    // If you want to establish a DTLS secured connection, you need to alter the security
    // information:
    // lwm2m_server_security_preshared(123, "publicid", "password", sizeof("password"));
}

void loop() {
    time_t tv_sec;

    //print_state(client_context);

    uint8_t result = lwm2m_step(client_context, &tv_sec);
    if (result == COAP_503_SERVICE_UNAVAILABLE)
        printf("No server found so far\n");
    else if (result != 0)
        printf("lwm2m_step() failed: 0x%X\n", result);

    lwm2m_network_process(client_context);
}

