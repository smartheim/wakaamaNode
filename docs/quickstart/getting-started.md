Periodic synchronisation and checking tests with newest platformio code may cause tests in the master branch to fail, please use a tagged release of the library in this case.
If the tests do not fail, it is safe to assume that the library works as expected. 

Current status: [![Build Status](https://travis-ci.org/Openhab-Nodes/wakaamaNode.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/wakaamaNode)

## Installing WakamaNode for [PlatformIO](http://platformio.org) development

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

* Network stack: Compile with *POSIX_NETWORK* for posix network sockets or with *LWIP* for the lwIP stack support.
  Windows and Unix/Linux builds automatically pick the posix/bsd socket API if *LWIP* is not set.
* Platform (memory, time): Compile with *ESP8266* for ESP8266 SDK support, *POSIX* for posix/windows system functions, *FREERTOS* for freeRTOS support.
  Windows and Unix/Linux builds automatically pick the posix/windows platform code.


## CMake build system
If you target an non-embedded system like Linux, Mac OS, Windows, you may use the cmake build system instead.

* Download the library https://github.com/Openhab-Nodes/wakaamaNode/archive/master.zip
* Extract the archive to `wakaamaNode`
* Include the `wakaamaNode/src/src.cmake` file like in the following example
* Create and change to your `build` dir.
* Execute `cmake ../`

```cmake
project(YOUR_PROJECT)
include(${CMAKE_CURRENT_LIST_DIR}/wakaamaNode/src/src.cmake)

add_executable(${PROJECT_NAME} ${YOUR_FILES} ${WAKAAMA_NODE_DIR_SOURCES})

# We need C++11 and C11 support
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE {WAKAAMA_NODE_DIR_INCLUDE_DIRS})

# Some definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS})
```

## Bare minimum sketch

Some key aspects of the library are shown in the example below. In particular:

* How to connect to a lwm2m server, if enabled with a preshared key DTLS connection. (It is assumed that you are network connected already.)
* How to set device describing attributes.
* How to use a predefined object and object instance: In this case object 3311 (light control).
* How to react to an object write via the `verifyWrite` function.
* How to update an object instance resource via the `lights.resChanged` call.

### Headers and long living objects

Include required headers and define your lwm2m objects, instances and the lwm2m client context:

```cpp
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
// automatically disconnected from all connected servers automatically.
LwM2MConnect context("testClient");
```

### Device infomation

Tell the lwm2m client context about your device:

```cpp
inline void setupDeviceInfo() {
    context.deviceInstance.manufacturer = "test manufacturer";
    context.deviceInstance.model_name = "test model";
    context.deviceInstance.device_type = "sensor";
    context.deviceInstance.firmware_ver = "1.0";
    context.deviceInstance.serial_number = "140234-645235-12353";
    // if LWM2M_DEV_INFO_TIME is enabled
    context.deviceInstance.time_offset = 5;
    context.deviceInstance.timezone = "+05:00";
}
```

### Configure your lwm2m objects

Configure your lwm2m objects. In this case, we want a lwm2m light object (id: 3311)
and one instance. When a write happens on the instance, set a LED on/off:

```cpp
inline void configureLwm2mObjects() {

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
}
```

### Add lwm2m server(s)

Add lwm2m server and configure DTLS (if enabled):

```cpp
void setup() {
    setupDeviceInfo();
    configureLwm2mObjects();

    connectToYourNetwork();
    
    if (!context.socket_count())
        printf("Failed to open socket\n");
    
    // Add a lwm2m server with unique id 123, lifetime of 100s, no storing of
    // unsend messages. The host url is either coap:// or coaps://.
    context.add_server(123, "coap://192.168.1.18", 100, false);
    
    // Enter your DTLS connection information
    #ifdef LWM2M_WITH_DTLS
    context.use_dtls_psk(123, "publicid", "PSK", sizeof("PSK"));
    #endif
}
```

### Main event loop

Your main event loop need to call `context.process`. Also call `watch_and_reconnect` if you
want to automatically reconnect on a lost connection. On Posix you can call `block_wait` to
make the process sleep until udp activity or the next due time:

```cpp
void loop() {
    int result = context.process();
    if (result == COAP_503_SERVICE_UNAVAILABLE)
        printf("No server added! Call lwm2m_add_server()\n");
    else if (result == COAP_505_NO_NETWORK_CONNECTION)
        printf("No sockets open. Reinit the network!\n");
    else if (result == COAP_506_DTLS_CONNECTION_DENIED)
        printf("DTLS connection denied. Server may not know PSK for client %s\n", CTX(context)->endpointName);
    else if (result != 0) {
        // Unexpected error
        print_state(CTX(context));
    }
    // If a server connetion gets lost, the lwm2m state machine will change into
    // BOOTSTRAP_REQUIRED state. The following method will reset the state machine
    // and the next process() call will attempt a reconnect.
    context.watch_and_reconnect(/*cooldown until reconnect in sec*/5);
    
    // You may go into low power mode on an µC or use context.block_wait() on posix:
    context.block_wait(/*block time in sec if nothing to do*/20);
}

```

### Change resources and tell the server

Change resources on your object instances, but don't forget to call `resChanged`:
```cpp
// Toggle the led by a button press and inform the lwm2m server about the new state
void push_button_pressed(bool newState) {
    ledsInstance.OnOff = newState;
    digitalWrite(LED_BUILTIN, ledsInstance.OnOff);
    lights.resChanged(CTX(context), ledsInstance.id, (uint16_t)id3311::RESID::OnOff);
}
```

## Configure features with wakaama_config.h

Copy the
[<img src="../../assets/github.png" style="width:20px"> examples/nodemcu_with_led_object/src/wakaama_config.h](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/examples/nodemcu_with_led_object/src/wakaama_config.h)
file to your project or create a `wakaama_config.h` file in your project source directory with the following
content:

```cpp
// Put the library in client mode (you basically always need this)
#define LWM2M_CLIENT_MODE

// Enable json support
#define LWM2M_SUPPORT_JSON
    
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
See examples in
[<img src="../../assets/github.png" style="width:20px"> src/examples](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/src/examples).
The examples including a step-by-step how-to are explained in [Examples](/examples/).
