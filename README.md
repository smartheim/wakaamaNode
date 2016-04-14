# libWakaamaEmb [![Build Status](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb)

This repository serves as an Arduino and PlattformIO library and provides easy access to Wakaama.
Wakaama is a C implementation of the Open Mobile Alliance's LightWeight M2M protocol (LWM2M).

Lightweight M2M is a protocol from the Open Mobile Alliance for M2M or IoT device management
and communication. It uses CoAP, a light and compact protocol with an efficient resource data model,
for the application layer communication between LWM2M Servers and LWM2M Clients.

Each service on a constrained device/sensor/actor is modelled as an LWM2M object instance.
An object has a unique identifier and may have instances.
Some LWM2M object identifiers are standardised via the OMA Object & Resource Registry
(http://technical.openmobilealliance.org/Technical/technical-information/omna/lightweight-m2m-lwm2m-object-registry).

For example object 3311 is for light controls.

This library targets resource constrained devices, therefore the name libWakaamaEmb(edded).

## Features
* Always up-to-date/in-sync Wakaama code
* Platform integrations (posix/win32, esp8266-sdk, freertos)
* Network stack integration (posix, lwip)
* Firmware update integration (esp8266-sdk) _WIP_
* Easy lwm2m object definition API
* Use it as your client API. All necessary lwm2m objects are defined (security, server and device objects).

All functionallity is covered by tests.

## Target device requirements
A target device needs 5kb RAM and 30kb ROM for the library and some additional objects. An UDP
capable network stack, a basic understanding of expired time and a periodic call into the
library about every minute is required.

This library uses dynamic memory allocation, but will not cause
heap fragmentation if it is executed in the same thread, used as documented and does not have to
share the heap with other consumers.
You may influence the memory access by implementing ``lwm2m_malloc``, ``lwm2m_free`` and ``lwm2m_strdup``
accordingly.

## Continous integration and automatic synchronisation to the latest Wakaama sources
Travis CI is executed on every commit and additionally every week. The
CI script syncs the ``src/wakaama`` directory to the latest code found in the core directory of
https://github.com/eclipse/wakaama.git if all tests pass.

## Demo/Example
* An example for the ESP8266 and for linux is located in examples/.

## Usage
First you have to configure which features should be enabled.
Create a config_wakama.h file. Add one or more of the following features:

* LWM2M_DEV_INFO_BATTERY: Add a battery field to the device information. You have to update that field regulary.
* LWM2M_DEV_INFO_WIFI_METRICS: Enables the wifi object where you may provide information about the wifi strength, connected ssid etc.
* LWM2M_DEV_INFO_MEMORY: The total and free memory fields in the device information structure are enabled.
* LWM2M_DEV_INFO_TIME: You may provide current time, timezone, utc offset data.
* LWM2M_FIRMWARE_UPGRADES: Add a firmware version field to the device information and enables the firmware update object.

### Client API Usage
Without any custom objects, without error handling and without reducing cpu usage while no new packets
arrive a fully functional client could look like this:

```
lwm2m_context_t * lwm2mH = lwm2m_client_init("testClient");
lwm2m_network_init(lwm2mH, NULL);

while(1) {
    struct timeval tv = {5,0};
    uint8_t result = lwm2m_step(lwm2mH, &tv.tv_sec);
    lwm2m_network_process(lwm2mH);
}

lwm2m_network_close(lwm2mH);
lwm2m_client_close();
```

### Object definition API Usage
If you use the object definition API, you only need to provide an object description (meta object data)
and all read/write/execute handling is done for you.

You add such a custom object like this:
```
    // Create custom object with id 1024, allow instances to be created
    // by the server, and with the given meta object data.
    lwm2m_object_t* test_object = lwm2m_object_create(1024, true, test_object_get_meta());
    // You may manually add instances right after object creation
    lwm2m_object_instance_add(test_object, test_object_create_instance());
    lwm2m_add_object(lwm2mH, test_object);
```
Ideally you do this before you are connecting to a lwm2m server.
The meta object data is usually definied in your custom_object.c. We assume the following custom object:
```
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
 *

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

With the help of the OBJECT_META(object_struct, result_variable_name, write_verify_callback, ressources...) macro
we define the object description:

```
OBJECT_META(test_object_instance_t, test_object_meta, test_object_write_verify_cb,
    {O_RES_RW|O_RES_UINT8   , offsetof(test_object_instance_t,test)},
    {O_RES_E |O_RES_FUNCTION, offsetof(test_object_instance_t,execF)},
    {O_RES_RW|O_RES_DOUBLE  , offsetof(test_object_instance_t,dec)},
    {O_RES_RW|O_RES_INT16   , offsetof(test_object_instance_t,sig)}
);

lwm2m_object_meta_information_t *test_object_get_meta() {
    return &test_object_meta;
}
```

The ressources are described each with an entry of the following form:
`{RES_ACCESS | RES_TYPE, offsetof(object_struct, res_name)}`.

If you looked carefully at the object definition above, you see that _test_ is restricted to 0..128.
This is less that the data type allows, so we have to write our own input validation method and
make it known to the meta object via the third argument (write_verify_callback).

For the above example such a method could look like this:
```
bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    if(changed_res_id==1 && i->test > 128) return false;

    return true;
}
```

### Provide device information
The lwm2m device object that is implemented with the client API allows
you to describe your device in many aspects. This is quite easy by getting
a reference to the device data object and changing its values before you
connect to a lwm2m server. An example:

```
    device_instance_t * device_data = lwm2m_device_data_get();
    device_data->manufacturer = "test manufacturer";
    device_data->model_name = "test model";
    device_data->device_type = "sensor";
    device_data->firmware_ver = "1.0";
    device_data->serial_number = "140234-645235-12353";

    // do initalisation now
    lwm2m_context_t * lwm2mH = lwm2m_client_init("testClient");
```

If you change data after you have connected to a server, you need to call
`lwm2m_device_res_has_changed(res_id)` after the change.

#### Firmware update support
WIP: This does not work right now!

Implement the methods ``bool lwm2m_request_firmware_update(new_version_no, total_size)`` and ``bool lwm2m_receive_firmware(offset, data, size)``.

### License
This platform code and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v 1.0.
