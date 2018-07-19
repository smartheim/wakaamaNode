# Connection/Device/Firmware API

Find the documentation and examples for the connection C and C++ API in this document.
The last sections describe the device- and firware update API.

## Connection C-API

Include `lwm2m/c_connect.h`.

In your main file declare a variable of type `lwm2m_client_context_t`.

!!! example "Define a long living client context variable"
    `#!cpp lwm2m_client_context_t context;`

This type contains the lwm2m context of type `lwm2m_context_t`, that is required for most API calls.
Usually you do not need to access any of the member fields directly.

Because it is so common to extract the `lwm2m_context_t*`, there is the `CTX(context)` macro doing this for you.

!!! example "Example on how to use CTX"
    ```cpp
    lwm2m_client_context_t context;
    lwm2m_process(CTX(context));
    ```


```cpp
/**
 * @param context Wakaama client context. May not be NULL.
 * @param endpointName The server uses this name to identify a client over multiple sessions
 * @return Return 0 if socket binding failed. Otherwise returns the number
 *     of sockets the method could bind to (for IPv4 and IPv6 each on all available interfaces).
 */
uint8_t lwm2m_client_init(lwm2m_client_context_t* context, const char * endpointName);
``` 

Initialize the given wakaame client context and the network module.
Close the client context with `lwm2m_client_close()`.
 
```cpp
/**
 * @param context Wakaama client context. May not be NULL.
 */
void lwm2m_client_close(lwm2m_client_context_t* context);
```

Close the given wakaama client context.

Will release dynamically aquired ressources and calls lwm2m_network_close().
All added servers are gone after this call.
This will not release objects created by lwm2m_object_create.
 

```cpp
/**
 * @param contextP Wakaama context
 * @return Returns a wakaama error code (the result value of lwm2m_step())
 */
int lwm2m_process(lwm2m_context_t * contextP);
```
Call this method periodically. Internally it will process new network packages, perform the dtls handshake if necessary, as well as progress in the wakaamas state machine.

!!! info
    On Posix Systems you can call `lwm2m_block_wait(context, timeout_in_sec)` after *lwm2m_process* to wait for
    either received network packets or for the due time of the next event.

```cpp
/**
 * @param contextP Wakaama context
 * @param reconnectTime Reconnect time in seconds
 */
void lwm2m_watch_and_reconnect(wm2m_context_t * contextP, int reconnectTime);
```
Watch server connections and reset the lwm2m state machine to force reconnects,
if the current state is STATE_BOOTSTRAP_REQUIRED. Usually you want to call this after `lwm2m_process`
for automatic reconnection.

```cpp
/**
 * @param contextP Wakaama context
 * @return A pointer to the next due time in sec
 */
int* lwm2m_due_time(wm2m_context_t * contextP);
```

`lwm2m_process` need to be called periodically and will provide an internal value in seconds when the next call is due.
This function returns a pointer to this due time value. You can modify (decrease) the value if required (`lwm2m_watch_and_reconnect`
and the ssl handshake code are doing this for example). This will cause `lwm2m_block_wait` to return sooner than the given timeout.

```cpp
/**
 * @param contextP Wakaama context
 * @param timeout_in_sec A timeout value in seconds. The event loop will enter another interation after this time
 * even if no packet has been received or timer has timed out.
 * @return Returns the socket number that received a message or 0 if it was a timeout. -1 on error.
 */
int lwm2m_block_wait(lwm2m_context_t * contextP, int timeout_in_sec);
```

Blocks until new data is available on the sockets.

This is implemented for systems that have an epoll API call with POSIX sockets
(and on Windows with an emulated epoll API) and on LWIP/freertos.

 
```cpp
/**
 * @param contextP Wakaama context
 * @param shortServerID A unique server id
 * @param uri The server URI
 * @param lifetime A lifetime in seconds
 * @param storing If notifications should be stored and resend if a server connection was interruppted and then reconnected.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
bool lwm2m_add_server(lwm2m_context_t *contextP, uint16_t shortServerID,
                      const char* uri, uint32_t lifetime, bool storing);
```
Adds a new server to the lwm2m client. The client statemachine will try to connect to this
server with the next iteration (`lwm2m_process()`).

```cpp
/**
 * @param contextP A Wakaama client context
 * @param shortServerID A unique server id
 * @param publicId publicIdentity for DTLS. May be NULL if no secure connection is used.
 * The expected c-string is copied to a new memory location.
 * @param psk Passkey if DTLS is used. May be NULL. The byte array is copied to a new memory location.
 * @param pskLen Passkey length. Should be 0 if no passkey is used.
 * @return Return true if successfully added and false if aborted due to no memory.
 */
bool lwm2m_use_dtls_psk(lwm2m_context_t *contextP, uint16_t shortServerID, const char* publicId,
                        const char* psk, unsigned short pskLen);
```
Alters a servers security details by adding preshared key DTLS information. Call this before entering the
main loop (`lwm2m_process()`).
You may also remove DTLS information by providing a NULL argument to psk and publicid.

!!! warning
    If you have specified a "coap://" URI in lwm2m_add_server(...), then
    publicId and psk will be set to NULL on the next connection attempt.

The LwM2M specification V1.0 says:

!!! quote
    Since the security of the default PSK Cipher Suites
    rely on the length and the entropy of this shared secret
    it is RECOMMENDED to provision a 16 byte (128 bit) key".

```cpp
/**
 * @param contextP Wakaama context
 * @param security_instance_id The security instance id which refers to a specific server
 */
bool lwm2m_unregister_server(lwm2m_context_t *contextP, uint16_t security_instance_id);
```

Informs the lwm2m server about a disconnect and flags the connection as disconnected.
Disconnected servers are still available until `lwm2m_remove_unregistered_servers` is called.

```cpp
/**
 * @param contextP Wakaama context
 */
void lwm2m_remove_unregistered_servers(lwm2m_context_t *contextP);
```
Removes all unregistered server, by removing all related security objects.
Puts the client back to STATE_INITIAL if the server list has been altered.

```cpp
/**
 * @param contextP Wakaama context
 * @param security_instance_id The security instance id which refers to a specific server
 */
const char* lwm2m_get_server_uri(lwm2m_context_t *contextP, uint16_t shortServerID);
```
Returns the uri of a server by providing the security object id of that server connection.

The c-string is not copied and valid as long as the respective security object is alive.


```cpp
/**
 * @param contextP Wakaama context
 */
bool lwm2m_is_connected(lwm2m_context_t *contextP);
```

Return true if wakaama is connected to a lwm2m server.

### Example

To setup the library, you would follow the outlined schema of the following C code:

```cpp
// The client name will be used by the lwm2m server for identification.
lwm2m_client_context_t context("testClient");
// Posix and Lwip network support is implemented.
lwm2m_client_init(&context);

while(1) {
   // Call the lwm2m state machine (lwm2m_process) periodically. 
   int result = lwm2m_process(CTX(context));
   /* result error processing ... */
   lwm2m_watch_and_reconnect(CTX(context), /*cooldown until reconnect in sec*/5);
   #ifdef POSIX_NETWORK
   lwm2m_block_wait(CTX(context), /*block time in sec if nothing to do*/20);
   #endif
}

// Deregisters from the lwm2m server, frees ressources taken by wakaama.
// Also closes the network connection and release network ressoures.
lwm2m_client_close(&context);
```

## Connection C++-API

The C++ API is only a slim wrapper around the C API.
All methods are named the same (expect the missing `lwm2m_` prefix)
and have the same signature as their C-equivalent,
except that no `lwm2m_context_t` need to be passed.

Include `lwm2m/connect.h`.

```cpp
class LwM2MConnect : public lwm2m_client_context_t {
public:
    LwM2MConnect(const char * endpointName);
    ~LwM2MConnect();
    
    int process();
    
    int block_wait(int timeout_in_sec);
    
    void watch_and_reconnect(int reconnect_time_in_sec);
    
    int* due_time();

    bool add_server(uint16_t short_server_id, const char* uri, uint32_t lifetime, bool storing);

    bool use_dtls_psk(uint16_t short_server_id, const char* publicId, const char* psk, unsigned short psk_len);
    
    bool unregister_server(uint16_t security_instance_id);
    
    void remove_unregistered_servers();
    
    const char* get_server_uri(uint16_t short_server_id);
    
    bool is_connected();
};
```


### Example

To setup the library, you would follow the outlined schema of the following CPP code:

```cpp
LwM2MConnect context("testClient");

while(1) {
   int result = context.process();
   /* result error processing ... */
   context.watch_and_reconnect(/*cooldown until reconnect in sec*/5);
   #ifdef POSIX_NETWORK
   context.block_wait(/*block time in sec if nothing to do*/20);
   #endif
}
```

## Device information API
The library implements the lwm2m device object for you.

> The Device Object provides an optional device reboot and factory reset function as well as a range of device related information which can be queried by the LWM2M Server.

```cpp
/**
 * @param res_id The ressource id of the value you have changed in device_instance_t.
 */
void lwm2m_device_res_has_changed(lwm2m_context_t *context, uint16_t res_id);
```

Call this if you have changed a ressource of the `device_instance_t` object.
You only have to do this after you have connected to a lwm2m server.

To change a device information (version number etc), do the following:
```cpp
lwm2m_client_context_t context; // Your global client context variable

context.deviceInstance.firmware_ver = "1.2";
// Only do this if you have called lwm2m_process at least once already
lwm2m_device_res_has_changed(CTX(context), RES_O_FIRMWARE_VERSION);
```

The following device information are obtained by calling a function:

| ResID |       Name       |       Configuration option      | Function                       |
|-------|:----------------:|:-------------------------------:|--------------------------------|
| 9     | Battery level    |  LWM2M_DEVICE_INFO_WITH_BATTERY | uint8_t lwm2m_get_bat_level()  |
| 20    | Battery status   |               same              | uint8_t lwm2m_get_bat_status   |
| 10    | Free memory      |  LWM2M_DEVICE_INFO_WITH_MEMINFO | int64_t lwm2m_get_free_mem()   |
| 21    | Total memory     |               same              | int64_t lwm2m_get_total_mem()  |
| 11    | Last error code  |  LWM2M_DEVICE_INFO_WITH_ERRCODE | int64_t lwm2m_get_last_error() |
| 13    | Current time (s) |                                 | int64_t lwm2m_gettime()        |

You need to implement the corresponding function if you enable the respective configuration option.

!!! info "Notify the server about a new value"
    `lwm2m_device_res_has_changed(CTX(context), RES_O_BATTERY_LEVEL)`

Some configuration options require you to implement further functions, see the table below:

| ResID |       Name       |       Configuration option      | Function                       |
|-------|:----------------:|:-------------------------------:|--------------------------------|
| 4     | Reboot device    |     LWM2M_DEVICE_WITH_REBOOT    | void lwm2m_reboot()            |
| 5     | Factory reset    | LWM2M_DEVICE_WITH_FACTORY_RESET | void lwm2m_factory_reset()     |

### Example

You may want to provide some c-strings stating the manufacturer, the model_name, device_type,
firmware version and a serial number, before you connect to a lwm2m server.
You would do this like in the following example:

```cpp
// C-API
lwm2m_client_context_t context;
lwm2m_client_init(&context, "testClient");

// C++ API
LwM2MConnect context;

context.deviceInstance.manufacturer = "test manufacturer";
context.deviceInstance.model_name = "test model";
context.deviceInstance.device_type = "sensor";
context.deviceInstance.firmware_ver = "1.0";
context.deviceInstance.serial_number = "140234-645235-12353";
// if LWM2M_DEV_INFO_TIME is enabled
context.deviceInstance.time_offset = 5;
context.deviceInstance.timezone = "+05:00";
```

!!! info
    If you change data after you have connected to a server, you need to call
    `lwm2m_device_res_has_changed(context, res_id)` after the change.

## Firmware update / OTA

To enable OTA, define LWM2M_FIRMWARE_UPGRADES in `config_wakama.h`.

An implementation exist for posix/win32 systems and for Arduino OTA compliant platforms.

### Update method

There are generally two methods for updating.

* The Http(s) method signals the lwM2M server that a URL should be provided where the new firmware can be found.
  Use UPDATE_PROTOCOL_HTTP or UPDATE_PROTOCOL_HTTPS for the `FirmwareUpdate` constructor.

* The Coap(s) method makes the server send the new firmware via coap as an opaque data chunk.
  Because that data chunk is expected to be huge and need to be memory buffered, small µC probably do not support this method.
  Use UPDATE_PROTOCOL_COAP or UPDATE_PROTOCOL_COAPS for the `FirmwareUpdate` constructor.

### C++ API

Include the `firmware.h` file and create an object of `FirmwareUpdate`.

```cpp
/**
* Creates a firmware update object.
*
* @param context A lwm2m context
* @param app_version The current APP version
*/
FirmwareUpdate::FirmwareUpdate(lwm2m_context_t *context, const char* app_version,
    lwm2m_update_protocol protocol);

/**
* Only for POSIX compatible systems.
* Check if this executable is the new updated one.
* If this is the new one:
* Waits for the old executable to finish. We expect a
* command line parameter "oldexe=PID" with the PID of the
* old executable. To notify the old executable about our
* successful start up, a POSIX signal USR1 is send.
*
* @param argc Command line argument count
* @param argv Command line arguments
*/
void FirmwareUpdate::checkIsUpdated(int argc, char** argv);

/**
* Call this in your main loop to check for new updates,
* initiate the download and restart if necessary
*/
void FirmwareUpdate::process();
```

### Example

```cpp
#include "lwm2m/firmware.h"
LwM2MConnect context;
FirmwareUpdate firmwareUpdate(CTX(context), "1.0", UPDATE_PROTOCOL_HTTP);

...

void loop() {
    context.process(...);
    firmwareUpdate.process();
}
...
// if POSIX
int main(int argc, char** argv) {
    firmwareUpdate.checkIsUpdated(argc, argv);
    ...
    while (1) loop();
    return 0;
}
```
