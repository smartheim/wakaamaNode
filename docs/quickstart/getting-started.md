This *Getting Started* guide assumes you have an ESP8266 board with an user-configurable LED, like a NodeMCU DevKit or a Linux/Windows system.

## Installing WakamaNode for [PlatformIO](http://platformio.org) development

There is a YouTube video with instructions:

[<img src="../../assets/youtube.png" style="width:20px">  How to install WakamaNode library in Visual Studio Code for PlatformIO](https://www.youtube.com/watch?v=bH3KfFfYUvg)

In a terminal, run `platformio lib install WakamaNode`.

Add this in your **platformio.ini** for the development branch:

```
lib_deps = git+https://github.com/Openhab-Nodes/wakaamaNode.git#master
```

Add this in your **platformio.ini** for the release branch:

```
lib_deps = git+https://github.com/Openhab-Nodes/wakaamaNode.git#v1.0
```

Dependencies are installed automatically.


Some build flags can to be provided to enable certain platform codes:

* Network stack: Compile with *POSIX_NETWORK* for posix network sockets or with *LWIP* for the lwIP stack support. Windows and Unix/Linux builds automatically pick the posix/bsd socket API if *LWIP* is not set.
* Platform (memory, time): Compile with *ESP8266* for ESP8266 SDK support, *POSIX* for posix/windows system functions, *FREERTOS* for freeRTOS support. Windows and Unix/Linux builds automatically pick the posix/windows platform code.


### CMake
If you target an x86 system, you may use the cmake buildsystem instead.
Just include the `.cmake` file of the src directory like in the following example:

```cmake
include(${CMAKE_CURRENT_LIST_DIR}/lib/wakaamaNode/src/wakaama_simple_client.cmake)

add_executable(${PROJECT_NAME} ${YOUR_FILES} ${WAKAAMA_SIMPLE_CLIENT_SOURCES})
# We need C++11 and C11 support
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

target_include_directories(${PROJECT_NAME} PRIVATE {WAKAAMA_SIMPLE_CLIENT_INCLUDE_DIRS})
```

## Bare minimum sketch

The following example shows you some key aspects of the library. In particular:

* How to connect to a lwm2m server, if enabled with a preshared key DTLS connection. (It is assumed that you are network connected already.)
* How to set device describing attributes.
* How to use a predefined object and object instance: In this case object 3311 (light control).
* How to react to an object write via the `verifyWrite` function.
* How to update an object instance resource via the `lights.resChanged` call.

```cpp
#include <new>
#include <time.h>
#include <Arduino.h>

#include "lwm2m/connect.h"
#include "lwm2m/objects.h"
#include "lwm2m/debug.h"

#include "lwm2mObjects/3311.h"

using namespace KnownObjects;

id3311::object lights;
id3311::instance ledsInstance;

// If this context object goes out of scope, you will be
// disconnected from all connected servers automatically.
LwM2MConnect context("testClient");

void setup() {
    std::set_new_handler([](){ESP.restart();}); // Reboot on heap memory outage

    context.deviceInstance.manufacturer = "test manufacturer";
    context.deviceInstance.model_name = "test model";
    context.deviceInstance.device_type = "sensor";
    context.deviceInstance.firmware_ver = "1.0";
    context.deviceInstance.serial_number = "140234-645235-12353";
    // if LWM2M_DEV_INFO_TIME is enabled
    context.deviceInstance.time_offset = 5;
    context.deviceInstance.timezone = "+05:00";

    // Overwrite the verify function and "abuse" it as value changed event.
    lights.verifyWrite = [](id3311::instance* i, uint16_t res_id) {
        // Is it instance 0 and the OnOff resource?
        if (i->id == 0 && res_id == id3311::RESID::OnOff) {
            // Change the led pin depending on the OnOff value
            digitalWrite(LED_BUILTIN, i->OnOff);
        }
        // Return true to accept the value and ACK to the server
        return true;
    };

    ledsInstance.id = 0; // set instance id
    lights.addInstance(CTX(context), &ledsInstance);
    lights.registerObject(CTX(context), false);

    // Initialize the LED_BUILTIN pin as an output
    pinMode(LED_BUILTIN, OUTPUT);

    // Wait for network to connect

    if (!context.socket_count())
        printf("Failed to open socket\n");
    
    // Connect to the lwm2m server with unique id 123, lifetime of 100s, no storing of
    // unsend messages. The host url is either coap:// or coaps://.
    context.add_server(123, "coap://192.168.1.18", 100, false);
    
    // Enter your DTLS connection information
    #ifdef LWM2M_WITH_DTLS
    context.use_dtls_psk(123, "publicid", "PSK", sizeof("PSK"));
    #endif
}

// Toggle the led by a button press and inform the lwm2m server about the new state
void push_button_pressed(bool newState) {
    ledsInstance.OnOff = newState;
    digitalWrite(LED_BUILTIN, ledsInstance.OnOff);
    lights.resChanged(CTX(context), ledsInstance.id, (uint16_t)id3311::RESID::OnOff);
}

void loop() {
    struct timeval time_to_next_call{20,0};

    int result = context.process(&time_to_next_call);
    if (result == COAP_505_NO_NETWORK_CONNECTION) {
        // Couldn't open UDP sockets.
        // Call lwm2m_network_init again after network is availabe again.
    } else if (result != 0) {
        // Unexpected error
        print_state(CTX(context));
    }
    // If a server connetion gets lost, the lwm2m state machine will change into
    // BOOTSTRAP_REQUIRED state. The following method will reset the state machine
    // and the next process() call will attempt a reconnect.
    context.watch_and_reconnect(&time_to_next_call, 5);
    
    // You may go into low power mode on an µC or use context.block_wait() on posix:
    context.block_wait(&next_event);
}

```

## Configure features with wakaama_config.h

Copy the
[<img src="../../assets/github.png" style="width:20px"> examples/nodemcu_with_led_object/src/wakaama_config.h](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/examples/nodemcu_with_led_object/src/wakaama_config.h)
file to your project or create a `wakaama_config.h` file in your project source directory with the following
content:

```cpp
// Enables the wifi object where you may provide information about the wifi strength, connected ssid etc.
#define LWM2M_DEV_INFO_WIFI_METRICS

// Allows to perform a reboot of the device. Implement lwm2m_reboot() for this to work.
#define LWM2M_DEVICE_WITH_REBOOT

// Allows to perform a factory reset. Implement lwm2m_factory_reset() for this to work.
// In this method you should erase all user memory, connection setups and so on.
#define LWM2M_DEVICE_WITH_FACTORY_RESET

// Implement lwm2m_get_bat_level() and lwm2m_get_bat_status().
#define LWM2M_DEVICE_INFO_WITH_BATTERY

// Implement lwm2m_get_free_mem() and lwm2m_get_total_mem().
#define LWM2M_DEVICE_INFO_WITH_MEMINFO

// Implement lwm2m_get_last_error() and lwm2m_reset_last_error().
#define LWM2M_DEVICE_INFO_WITH_ERRCODE

// Implement lwm2m_gettime() and update the fields  **timezone** and **time_offset**
// of the device information object.
#define LWM2M_DEVICE_INFO_WITH_TIME

// Adds a **hardware_ver** and a **software_ver** c-string field.
#define LWM2M_DEVICE_INFO_WITH_ADDITIONAL_VERSIONS

// Enables the firmware update mechanism.
#define LWM2M_FIRMWARE_UPGRADES

// Enable DTLS support (preshared and public key)
#define LWM2M_WITH_DTLS

// Enable additional support for X.509 certificates and PEM data
// #define LWM2M_WITH_DTLS_X509

// Overwrite maximum packet size. Defaults to 1024 bytes
// #define MAX_PACKET_SIZE 1024
```

Edit the file to your needs, by commenting out unwanted features.

## Demo/Example
An example for the ESP8266 and for linux/windows is located in
[<img src="../../assets/github.png" style="width:20px"> src/examples](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/src/examples).

* Execute ``pio run -e esp01`` or ``pio run -e nodemcu`` to compile an example with a predefined lwm2m object (the light control object) to switch the built-in led. Use ``pio run -e esp01 -t upload`` to upload the example.
* Execute ``pio run -e native`` to compile a linux/windows compatible example for switching on/off the current monitor screen. The firmware provides a lwm2m object (res id 1024) with a boolean state ressource at ID 0 for switching the screen on/off. At ID 1 there a read only string ressource which states the host name and at ID 2 there is a read only "name" string ressource.

