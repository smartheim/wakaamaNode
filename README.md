# libWakaamaEmb [![Build Status](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/libWakaamaEmb)

This library targets Arduino and PlattformIO and provide Wakaama mainly for resource constrained devices.
Wakaama is a C implementation of the Open Mobile Alliance's LightWeight M2M protocol (LWM2M).

Lightweight M2M is a protocol from the Open Mobile Alliance for M2M or IoT device management
and communication. It uses CoAP, a light and compact protocol with an efficient resource data model,
for the application layer communication between LWM2M Servers and LWM2M Clients.

Each service on a constrained device/sensor/actor is modelled as an LWM2M object instance.
An object has a unique identifier and may have instances.
Some LWM2M object identifiers are standardised via the OMA Object & Resource Registry
(http://technical.openmobilealliance.org/Technical/technical-information/omna/lightweight-m2m-lwm2m-object-registry).

For example object 3311 is for light controls.

The target LWM2M Devices for this library are mainly resource constrained devices, therefore
the name libWakaamaEmb(edded). 

### Target device requirements
A target device needs 5kb RAM and 30kb ROM for the library and some additional objects. An UDP
capable network stack, a basic understanding of expired time and a periodic call into the
library about every minute is required.

This library uses dynamic memory allocation, but will not cause
heap fragmentation if it is executed in the same thread, used as documented and does not have to
share the heap with other consumers.
You may influence the memory access by implementing ``lwm2m_malloc``, ``lwm2m_free`` and ``lwm2m_strdup``
accordingly.

### Continous integration and automatic synchronisation to the latest Wakaama sources
Travis CI is executed on every commit and additionally every week. The
CI script syncs the ``src/wakaama`` directory to the latest code found in the core directory of
https://github.com/eclipse/wakaama.git if all tests pass.

### Demo/Example
* An example for the ESP8266 is located in examples/.

### Usage
First you have to configure which features should be enabled.
Create a config_wakama.h file. Add one or more of the following features:

* LWM2M_WITH_JSON: Enables json support
* LWM2M_DEV_INFO_BATTERY: Add a battery field to the device information. You have to update that field regulary.
* LWM2M_DEV_INFO_WIFI_METRICS: Enables the wifi object where you may provide information about the wifi strength, connected ssid etc.
* LWM2M_DEV_INFO_MEMORY: The total and free memory fields in the device information structure are enabled.
* LWM2M_DEV_INFO_TIME: You may provide current time, timezone, utc offset data.
* LWM2M_FIRMWARE_UPGRADES: Add a firmware version field to the device information and enables the firmware update object.

#### Initialize
Call ``lwm2m_init_wakaama(name)`` to initialize wakaama. This will
callback on you via the function ``lwm2m_dev_info``, where you can provide
the model no, serial no, firmware/hardware versions, manufacturer name and so on.

Add your objects via ``lwm2m_add_object``.

Connect to a server by setting up a bootstrap structure and calling ``lwm2m_add_factory_bootstrap_information``.
This will open up a udp connection.

Now you only have to call ``lwm2m_periodic`` regulary.

#### Firmware update support
Implement the methods ``bool lwm2m_request_firmware_update(new_version_no, total_size)`` and ``bool lwm2m_receive_firmware(offset, data, size)``.

### Porting
src/platform_esp8266.c implements the following methods:

* lwm2m_malloc(size_t s)
* void lwm2m_free(void * p)
* char * lwm2m_strdup(const char * str)
* int lwm2m_strncmp(const char * s1, const char * s2,  size_t n)
* time_t lwm2m_gettime(void)
* void lwm2m_printf(const char * format, ...)

src/network_lwip_sockets.c implements the following methods:
* ``uint8_t lwm2m_buffer_send(void * sessionH,  uint8_t * buffer, size_t length, void * userdata)``
* ``bool lwm2m_session_is_equal(void * session1, void * session2, void * userData)``
* ``void * lwm2m_connect_server(uint16_t secObjInstID, void * userData)``
* ``void * lwm2m_create_socket()`` // Returns socket identifier
* ``void lwm2m_free_socket(void * socket)`` // Free socket
* ``bool lwm2m_has_data(void * socket)`` // Return true if a new data packet is received
* ``int lwm2m_receive_data(void * socket, uint8_t * buffer, int buffer_size)`` // Copies received data to buffer and return size of data
* ``bool udp_bind_to_coap_server(void * socket, char * uri)`` // Return true if binding to the given address succeeded.
  // uri is for example: coap://a-coap-server.org or coaps://192.168.0.107

### License
This platform code and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v 1.0.
