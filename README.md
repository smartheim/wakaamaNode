# libWakaamaNodes [![Build Status](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb)

This repository serves as an Arduino* and PlattformIO library and provides easy access to Wakaama.
Wakaama is a C implementation of the Open Mobile Alliance's LightWeight M2M protocol (LWM2M).

Lightweight M2M is a protocol from the Open Mobile Alliance for M2M or IoT device management
and communication. It uses CoAP, a light and compact protocol with an efficient resource data model,
for the application layer communication between LWM2M Servers and LWM2M Clients.

Each service on a constrained device/sensor/actor is modelled as an LWM2M object instance.
An object has a unique identifier and may have instances.
Some LWM2M object identifiers are standardised via the OMA Object & Resource Registry
(http://technical.openmobilealliance.org/Technical/technical-information/omna/lightweight-m2m-lwm2m-object-registry).

For example object 3311 is for light controls.

## Features
* Always up-to-date/in-sync Wakaama code (uses a Travis CI daily cron job)
* Platform integrations (posix/win32, esp8266-sdk, freertos)
* Network stack integration (posix, lwip)
* Firmware update integration (esp8266-sdk) _WIP_
* Easy lwm2m object definition API
* Use it in addition to the wakaama client API. All necessary lwm2m objects are defined for you (security, server and device objects).
* This library targets resource constrained devices and most of the API can be used without dynamic heap allocations.
* All API functionallity and libWakaamaNodes<-->wakaama server communication is covered by tests.

## Target device requirements
A target device needs 5kb RAM and 30kb ROM for the library and some additional objects. An UDP
capable network stack, a basic understanding of expired time and a periodic call into the
library about every minute is required.

Most of the API can be used in a staticly allocated memory environment. Wakaama on the other hand, uses
dynamic memory allocation. This will not cause heap fragmentation though as long as lwm2m object creation takes place it in the same thread.
You may influence the memory layout and access by implementing ``lwm2m_malloc``, ``lwm2m_free`` and ``lwm2m_strdup`` accordingly.

## Continous integration and automatic synchronisation to the latest Wakaama sources
Travis CI is executed on every commit and additionally every day by https://nightli.es/. The
CI script syncs the ``src/wakaama`` directory to the latest code found in the core directory of
https://github.com/eclipse/wakaama.git. This may cause tests to fail, please use an older release
of the library, wait for a fix to appear or contribute a fix yourself. :)

## Buildsystems
This library is published to the PlatformIO library registry and Arduino library registry
and available on Github. TODO links.

### Arduino
The Arduino platform is not supported out of the box right now. The wakaama library needs
compile time definitions and they are not availabe for libraries so far (version 1.8.3).

### PlatformIO
Either copy this direcory to a "wakaamaNode" directory under your projects "lib" folder or
install the library via the registry (``pio lib install wakaamaNode``).

### CMake
Just include the `.cmake` file of the src directory like in the following example:

```cmake
include(${CMAKE_CURRENT_LIST_DIR}/lib/wakaamaNode/src/wakaama_simple_client.cmake)

add_executable(${PROJECT_NAME} ${YOUR_FILES} ${WAKAAMA_SIMPLE_CLIENT_SOURCES})
# We need C++11 and C11 support
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

target_include_directories(${PROJECT_NAME} PRIVATE {WAKAAMA_SIMPLE_CLIENT_INCLUDE_DIRS})
```

## Demo/Example
An example for the ESP8266 and for linux is located in `examples/`.

* Execute ``pio run -e esp01`` or ``pio run -e nodemcu`` to compile an example with a simple l2mwm object (res id 1024) with a boolean state ressource at ID 0. True/False switches the BUILTIN_LED on/off. Use ``pio run -e esp01 -t upload`` to upload the example.
* Execute ``pio run -e native`` to compile a linux/windows compatible example for switching on/off the current monitor screen. The firmware provides a lwm2m object (res id 1024) with a boolean state ressource at ID 0 for switching the screen on/off. At ID 1 there a read only string ressource which states the host name and at ID 2 there is a read only "name" string ressource.

## Client API
A fully functional client could look as simple as this:

```cpp
// The client name will be used by the lwm2m server for identification.
lwm2m_context_t * lwm2mH = lwm2m_client_init("testClient");
// You don't need to use the network helper methods. If you do, call
// the lwm2m_network_init() method early in your code.
// Posix and Lwip network support is implemented.
lwm2m_network_init(lwm2mH, NULL);

while(1) {
   // Call the lwm2m state machine (lwm2m_step) periodically. 
   // tv will be used as output variable. Wakaama tells us about the next required call to lwm2m_step().
   // In this simple example we ignore this request and call the state machine in each main loop cycle.
   struct timeval tv = {5,0};
   uint8_t result = lwm2m_step(lwm2mH, &tv.tv_sec);
   // let the network stack do its thing.
   lwm2m_network_process(lwm2mH);
}

// Deregisters from the lwm2m server, frees ressources taken by wakaama.
lwm2m_client_close();
// Close the network connection and release network ressoures.
lwm2m_network_close(lwm2mH);
```

In this section you will also learn how to define a custom object and how to provide
information like the device name, manufacturer, wifi signal strength or serial number to the device object.

### Object definition API Usage
If you use the object definition API, you only need to provide an object description (meta object data)
and all read/write/execute handling is done for you. You add such a custom object like this:

```cpp
    // Create custom object with id 1024, allow instances to be created
    // by the server, and with the given meta object data.
    lwm2m_object_t* test_object = lwm2m_object_create(1024, true, test_object_get_meta());
    // You may manually add instances right after object creation
    lwm2m_object_instance_add(test_object, test_object_create_instance());
    lwm2m_add_object(lwm2mH, test_object);
```

Ideally you do this before you are connecting to a lwm2m server.
The meta object data is usually definied in your custom_object.c. We assume the following custom object:

```cpp
 **/
 *                 Multiple
 * Object |  ID  | Instances | Mandatoty |
 *  Test  | 1024 |    Yes    |    No     |
 *
 *  Ressources:
 *              Supported    Multiple
 *  Name | ID | Operations | Instances | Mandatory |  Type   | Range | Units |      Description      |
 *  test |  0 |    R/W     |    No     |    Yes    | Integer | 0-128 |       |                       |
 *  exec |  1 |     E      |    No     |    Yes    |         |       |       |                       |
 *  dec  |  2 |    R/W     |    No     |    Yes    |  Float  |       |       |                       |
 *  sig  |  3 |    R/W     |    No     |    Yes    | Integer |       |       | 16-bit signed integer |
 **/

typedef struct
{
    struct test_object_instance_t * next;   // matches lwm2m_list_t::next
    uint16_t shortID;                       // matches lwm2m_list_t::id

    uint8_t  test;
    void*    execF; // function pointer
    double   dec;
    int16_t  sig;
} test_object_instance_t;
```

With the help of the ``OBJECT_META(object_struct, result_variable_name, write_verify_callback, ressources...)`` macro we define the object description:

```cpp
// The following is equal to this pseudo code:
// test_object_instance_t test_object_meta =
//            MetaBuilder().add(readwrite ID0 with type unsigned byte)
//                         .add(executable ID1 test_object_write_verify_cb)
//                         .add(readwrite ID2 with type double)
//                         .add(readwrite ID3 with type int16).build()
OBJECT_META(test_object_instance_t, test_object_meta, test_object_write_verify_cb,
    {0, O_RES_RW|O_RES_UINT8   , offsetof(test_object_instance_t,test)},
    {1, O_RES_E |O_RES_FUNCTION, offsetof(test_object_instance_t,execF)},
    {2, O_RES_RW|O_RES_DOUBLE  , offsetof(test_object_instance_t,dec)},
    {3, O_RES_RW|O_RES_INT16   , offsetof(test_object_instance_t,sig)}
);

lwm2m_object_meta_information_t *test_object_get_meta() {
    return &test_object_meta;
}
```

The ressources are described each with an entry of the following form:
`{RES_ID, RES_ACCESS | RES_TYPE, offsetof(object_struct, res_name)}`.

If you have looked carefully at the object definition above, you see that _test_ is restricted to 0..128.
This is less that the data type allows, so we have to provide an input validation method and
make it known to the meta object via the third argument (write_verify_callback).

For the above example such a method could look like this:

```cpp
bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    // Return false for an invalid object
    if(changed_res_id==1 && i->test > 128) return false;
    // If we return true, the new value will be applied to the instance object for us.
    return true;
}
```

### The lwm2m device object
The library implements the lwm2m device object for you.

    The Device Object provides a range of device related information which can be queried by the LWM2M Server, and a device reboot and factory reset function.

In this section you learn how to enable some optional information fields
of the device object and how to feed data into that object.

#### Configure features with config_wakama.h

Copy the `examples/nodemcu_with_led_object/config_wakama.h` file to your project
or create a `config_wakama.h` file in your project source directory with the following
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
```

Edit the file to your needs, by commenting out unwanted features.

#### Provide device information

You need to provide some static c-strings stating the manufacturer, the model_name, device_type,
firmware version and a serial number, before you connect to a lwm2m server (but after you called `lwm2m_client_init`).
You would do this like in the following example:

```cpp
    // do initalisation first
    lwm2m_context_t * lwm2mH = lwm2m_client_init("testClient");

    // Get the device object instance.
    device_instance_t * device_data = lwm2m_device_data_get();
    device_data->manufacturer = "test manufacturer";
    device_data->model_name = "test model";
    device_data->device_type = "sensor";
    device_data->firmware_ver = "1.0";
    device_data->serial_number = "140234-645235-12353";
    // if LWM2M_DEV_INFO_TIME is enabled
    device_data->time_offset = 5;
    device_data->timezone = "+05:00"
```

If you change data after you have connected to a server, you need to call
`lwm2m_device_res_has_changed(res_id)` after the change.

### Optional: Wifi connection information
WIP: This feature is in development!

### Optional: Firmware update support
WIP: This feature is in development!

You need to define LWM2M_FIRMWARE_UPGRADES in `config_wakama.h` as explained above.
Implement the following two callback methods:

* ``bool lwm2m_request_firmware_update(char* new_version_str, total_size)``: Return true if the new_version (provided as a c-string) is acceptable and if you have **total_size** (uint32_t) available space for the new firmware.
* ``bool lwm2m_receive_firmware_chunk(offset, data, chunkLength)``: The firmware is received in chunks, and you receive one chunk per callback of this method with the given **offset** (uint32_t), the **data** (const char*) and the chunk length. Return true if you want to receive further chunks until the transfer is complete, return false to stop the firmware receiving process.

## License
This platform code and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v 1.0.
