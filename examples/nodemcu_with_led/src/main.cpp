/*****
 Switch ESP8266 Led (LED_BUILTIN) via lwm2m.
 To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
*****/

#include <new>
#include <time.h>
#include <sys/time.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wifi_credentials.h"

#include "lwm2m/connect.h"
#include "lwm2m/network.h"
#include "lwm2m/objects.h"
#include "lwm2m/debug.h"

#include "lwm2mObjects/3311.h"

using namespace KnownObjects;

id3311::object lights;
id3311::instance ledsInstance;

LwM2MConnect context("testClient-WakaamaNode");

// Called by the device object for resource 4 (RES_M_REBOOT)
void lwm2m_reboot() {
    ESP.restart();
}

inline void setupDeviceInformation() {
    context.deviceInstance.manufacturer = "test manufacturer";
    context.deviceInstance.model_name = "test model";
    context.deviceInstance.device_type = "led";
    context.deviceInstance.firmware_ver = "1.0";
    context.deviceInstance.serial_number = "140234-645235-12353";
}

void dieBlinking() {
    while (1) {
        digitalWrite(LED_BUILTIN, true);
        delay(100);
        digitalWrite(LED_BUILTIN, false);
        delay(100);
    }
}

void setup() {
    // Reboot on heap memory outage
    std::set_new_handler(lwm2m_reboot);
    
    setupDeviceInformation();

    // Overwrite the verifyFunction and "abuse" it as value changed event.
    lights.verifyWrite = [](id3311::instance* inst, uint16_t res_id) {
        // Is it instance 0 and the OnOff resource?
        if (inst->id == 0 && res_id == id3311::RESID::OnOff) {
            // Change the led pin depending on the OnOff value
            digitalWrite(LED_BUILTIN, inst->OnOff);
        }
        // Return true to accept the value and ACK to the server
        return true;
    };

    ledsInstance.id = 0; // set instance id
    lights.addInstance(CTX(context), &ledsInstance);
    lights.registerObject(CTX(context), false);

    // Initialize the LED_BUILTIN pin as an output
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, false);

    // Wait for network to connect
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, true);
        delay(200);
        digitalWrite(LED_BUILTIN, false);
        delay(200);
    }

    digitalWrite(LED_BUILTIN, true);

    // Init lwm2m network
    if (!context.socket_count()) {
        printf("Failed to open socket\n");
        dieBlinking();
    }
    
    // Connect to the lwm2m server with unique id 123, lifetime of 100s, no storing of
    // unsend messages. The host url is either coap:// or coaps://.
    context.add_server(123, "coap://leshan.eclipse.org", 100, false);
    
    // Enter your DTLS secured connection information
    #ifdef LWM2M_WITH_DTLS
    context.use_dtls_psk(123, "publicid", "PSK", sizeof("PSK"));
    #endif
}

// Toggle the led with a button press and inform the lwm2m server about the new state
void push_button_pressed(bool newState) {
    ledsInstance.OnOff = newState;
    digitalWrite(LED_BUILTIN, ledsInstance.OnOff);
    lights.resChanged(CTX(context), ledsInstance.id, (uint16_t)id3311::RESID::OnOff);
}

// If you want to deep sleep. You should be so kind and let the lwm2m server know about the absence
void disconnect_from_lwm2m_server() {
    lwm2m_network_close(CTX(context));
    
    ESP.deepSleep(100);
    
    lwm2m_network_init(CTX(context), 0);
}

void loop() {
    struct timeval tv = {5,0};

    int result = context.process(&tv);
    if (result != 0) {
        // Unexpected error
        printf("lwm2m_step() failed: 0x%X\n", result);
        print_state(CTX(context));
    }
    context.watch_and_reconnect(&tv, 5);
}

