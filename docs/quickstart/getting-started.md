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

The following example shows how to connect to a lwm2m server, optionally with
a preshared key DTLS connection. It is still your responsibility to connect to the
wifi/network and to bootstrap the device with the lwm2m server address if it is not a fixed address.


```cpp
#include <Arduino.h>

#include "wakaama_simple_client.h"
#include "wakaama_network.h"
#include "wakaama_object_utils.h"

lwm2m_context_t * lwm2mH;

void setup() {
    // connect to network/wifi
    // ......
    
    // Tell something about this device. This will be published as lwM2M device object (#3).
    device_instance_t * device_data = lwm2m_device_data_get();
    device_data->manufacturer = "test manufacturer";
    device_data->model_name = "test model";
    device_data->device_type = "led";
    device_data->firmware_ver = "1.0";
    device_data->serial_number = "140234-645235-12353";
    
    // The client name will be used by the lwm2m server for identification.
    lwm2mH = lwm2m_client_init("testClient");
    
    // You don't need to use the network helper methods. If you do, call
    // the lwm2m_network_init() method early in your code.
    // Posix and LwIP network stacks are support
    lwm2m_network_init(lwm2mH, nullptr);
    
    // Add your lwm2m objects here
    // .....
    
    // Connect to the lwm2m server with unique id 123, lifetime of 100s, no storing of
    // unsend messages. The host url is either coap:// or coaps://.
    lwm2m_add_server(123, "coap://192.168.1.18", 100, false)
    
    // If you want to establish a DTLS secured connection, you need to alter the security
    // information:
    // lwm2m_server_security_preshared(123, "publicid", "PSK", sizeof("PSK"));
}

void disconnect() {
    // Deregisters from the lwm2m server, frees ressources taken by wakaama.
    lwm2m_client_close();
    // Close the network connection and release network ressoures.
    lwm2m_network_close(lwm2mH);
}

void loop() {
    // Call the lwm2m state machine (lwm2m_step) periodically. 
    // tv will be used as output variable.
    // Wakaama tells us about the next required call to lwm2m_step().    
    // In this simple example we ignore this request and call
    // the state machine in each main loop cycle.
    struct timeval tv = {5,0};
    uint8_t result = lwm2m_step(lwm2mH, &tv.tv_sec);
    
    // let the network stack do its thing.
    lwm2m_network_process(lwm2mH);
}
```

## Configure features with config_wakama.h

Copy the
[<img src="../../assets/github.png" style="width:20px"> examples/nodemcu_with_led_object/src/config_wakama.h](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/examples/nodemcu_with_led_object/src/config_wakama.h)
file to your project or create a `config_wakama.h` file in your project source directory with the following
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

// Enable DTLS support
#define LWM2M_WITH_DTLS
```

Edit the file to your needs, by commenting out unwanted features.

## Demo/Example
An example for the ESP8266 and for linux/windows is located in
[<img src="../../assets/github.png" style="width:20px"> src/examples](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/src/examples).

* Execute ``pio run -e esp01`` or ``pio run -e nodemcu`` to compile an example with a simple l2mwm object (res id 1024) with a boolean state ressource at ID 0. True/False switches the BUILTIN_LED on/off. Use ``pio run -e esp01 -t upload`` to upload the example.
* Execute ``pio run -e native`` to compile a linux/windows compatible example for switching on/off the current monitor screen. The firmware provides a lwm2m object (res id 1024) with a boolean state ressource at ID 0 for switching the screen on/off. At ID 1 there a read only string ressource which states the host name and at ID 2 there is a read only "name" string ressource.

