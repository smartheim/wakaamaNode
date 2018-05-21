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

#include <time.h>

#include <Arduino.h>

#include "wakaama_simple_client.h"
#include "wakaama_network.h"
#include "wakaama_object_utils.h"

#include "led_object.h"

lwm2m_context_t * client_context;
void setup() {
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

    // Create object
    lwm2m_object_t* test_object = lwm2m_object_create(5850, true, led_object_get_meta());
    lwm2m_object_instances_add(test_object, led_object_create_instances());
    lwm2m_add_object(client_context, test_object);

    // Initialize the BUILTIN_LED pin as an output
    pinMode(BUILTIN_LED, OUTPUT);     

    // Wait for network to connect

    // Init lwm2m network
    uint8_t bound_sockets = lwm2m_network_init(client_context, NULL);
    if (bound_sockets == 0)
        printf("Failed to open socket\n");
}

void loop() {
    time_t tv_sec;

    //print_state(client_context);

    uint8_t result = lwm2m_step(client_context, &tv_sec);
    if (result == COAP_503_SERVICE_UNAVAILABLE)
        printf("No server found so far\n");
    else if (result != 0)
        printf("lwm2m_step() failed: 0x%X\n", result);

    lwm2m_network_native_sock(client_context, 0);
    lwm2m_network_process(client_context);
}

