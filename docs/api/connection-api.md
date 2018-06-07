# Connection/Device API

The connection/device API is implemented in C.
This library is designed to be used as a single instance. You cannot request or manage multiple Wakaama contexts.

## Connection API

Include `wakaama_simple_client.h`.

```cpp
/**
 * @param endpointName The server uses this name to identify a client over multiple sessions
 * @return A wakaama context.
 */
lwm2m_context_t * lwm2m_client_init(const char * endpointName);
``` 

Initialize wakaame in client mode.
Will allocate objects and initializes them.
This method can only be called once! Close the client context with lwm2m_client_close().

```cpp
/**
 * @brief Return the context created by lwm2m_client_init().
 * @return A wakaama context.
 */
lwm2m_context_t * lwm2m_client_get_context(void);
```

```cpp
void lwm2m_client_close(void);
```

Close the wakaama client context and release dynamically aquired ressources.
This will not release objects created by lwm2m_object_create.

```cpp
/**
 * Adds a new server to the lwm2m client. The client statemachine will try to connect to this
 * server in the next iteration (usually caused by calling lwm2m_network_process(context)).
 * @param shortServerID A unique server id
 * @param shortServerID The server URI
 * @param lifetime A lifetime in seconds
 * @param storing If notifications should be stored and resend if a server connection was interruppted and then reconnected.
 * @param publicId publicIdentity for DTLS. May be NULL if no secure connection is used.
 * @param psk Passkey if DTLS is used. May be NULL.
 * @param pskLen Passkey length. Should be 0 if no passkey is used.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
bool lwm2m_add_server(uint16_t shortServerID, const char* uri, uint32_t lifetime, bool storing,
    const char* publicId, const char* psk, size_t pskLen);
```

```cpp
/**
 * Unregisteres from a connected server.
 * @param security_instance_id The security instance id which refers to a specific server
 */
bool lwm2m_unregister_server(uint16_t security_instance_id);
```

```cpp
/**
 * Removes all unregistered server, by removing all related security objects.
 * Puts the client back to STATE_INITIAL if the server list has been altered.
 */
void lwm2m_remove_unregistered_servers(void);
```

```cpp
/**
 * Returns the uri of a server by providing the security object id of that server connection.
 * @param security_instance_id The security instance id which refers to a specific server
 * @param uriBuffer The destination buffer
 * @param buffer_len The destination buffer length
 */
bool lwm2m_get_server_uri(uint16_t security_instance_id, char* uriBuffer, size_t buffer_len);
```

```cpp
/**
 * @brief Return true if wakaama is connected to a lwm2m server.
 * @return
 */
bool lwm2m_is_connected(void);
```

### Example

To setup the library, you would follow the the outlined schema of the following C code:

```cpp
// The client name will be used by the lwm2m server for identification.
lwm2m_context_t * lwm2mH = lwm2m_client_init("testClient");
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

## Provide device information API
The library implements the lwm2m device object for you.

> The Device Object provides a range of device related information which can be queried by the LWM2M Server, and a device reboot and factory reset function.

In this section you learn how to enable some optional information fields
of the device object and how to feed data into that object.


```cpp
device_instance_t * lwm2m_device_data_get(void);
```

Return the device information object.
Change this object before you connect to a server.

```cpp
/**
 * @param res_id The ressource id of the value you have changed in device_instance_t.
 */
void lwm2m_device_res_has_changed(uint16_t res_id);
```

Call this if you have changed a ressource in the device_instance_t object.
You only have to do this after you have connected to a lwm2m server.

To change a device information (version number etc), do the following:
```cpp
device_instance_t* device = lwm2m_device_data_get();
device->firmware_ver = "1.2";
lwm2m_device_res_has_changed(RES_O_FIRMWARE_VERSION);
```

Some device information are obtained by calling a function.
The battery level is an example.
Just call `lwm2m_device_res_has_changed(RES_O_BATTERY_LEVEL)` periodically or after
the battery level has changed and the runtime will retrieve the new data by
from `lwm2m_get_bat_level()`.


### Example

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

## Firmware update / OTA

To enable OTA, define LWM2M_FIRMWARE_UPGRADES in `config_wakama.h`.

An implementation exist for posix/win32 systems and for Arduino OTA compliant platforms.

Control how firmware updates can be performed by defining 
LWM2M_FIRMWARE_UPGRADE_METHOD to **HTTP**, **HTTPS** or **COAP**, **COAPS**. If you do no define
LWM2M_FIRMWARE_UPGRADE_METHOD, the best option is choosen.
ESP8266 prefers **HTTP**, posix/win32 systems prefer **COAP**.

The Http(s) method signals the lwM2M server that only firmware polling is enabled
and that a URL should be provided where the new firmware can be found.

The Coap(s) method makes the server send the new firmware via coap as an opaque data chunk.
Because that data chunk is expected to be huge and need to be memory buffered, ESP8266 does
not support this method.
