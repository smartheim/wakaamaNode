## lwm2m_process returns COAP_506_DTLS_CONNECTION_DENIED

If you are using DTLS: The server denied your request to connect. This is propably because the
PSK (Preshared key) known to the server for your clients endpoint name is different to the PSK of your client.

You should update the PSK on the server side to match the PSK you have given via `lwm2m_use_dtls_psk(.., PSK, PSK_LEN)`.

!!! note How to use lwm2m_use_dtls_psk
    The examples very often use **sizeof** as in `lwm2m_use_dtls_psk(CTX(context), 123, "publicid", "password", sizeof("password"));`.
    This means we define a PSK consisting of 8 characters starting with "p" and ending with "d". If you use `strlen` to count the
    PSK characters, you have defined a different PSK: starting with "p" and ending with a `0` with the length of 9.

If you are not connected via DTLS (you are using a "coap://" address instead of a "coaps://" adress) and you
get this message: At least the leshan lwm2m server denies "known" clients, that have a PSK entry in the leshan database, to connect
via a plain unsecured connection. You need to delete the PSK entry on leshan first.

## lwm2m_process returns COAP_503_SERVICE_UNAVAILABLE

No server is known to the library.
You have not called `lwm2m_add_server` (or the method failed to aquire heap memory).

## lwm2m_process returns COAP_505_NO_NETWORK_CONNECTION

See next section

## lwm2m_client_init (C-API)/ lwm2m.socket_count() (C++-API) returns 0 

Internally a UDP socket is allocated if `lwm2m_client_init` (C-API) is called or the client context `LwM2MConnect()` (C++-API) is created.

On LWIP this will usually fail if no heap memory is available anymore or if the maximum udp socket count has been reached.

On a POSIX system this can also happen if no interface exists on the host system, if no free port is available anymore or if the application has no permissions to create a UDP socket.

This is an unexpected condition and usually requires to restart the application. Alternatively you can
call `open_sockets = lwm2m_network_init(CTX(context), 0)` at some point if the resource shortage is solved.

Please always free the network resources, especially if you are creating lwm2m client contexts more than once in the lifetime of your application.
In C, you would do a `lwm2m_client_close`, in C++ you would make the client context object go out of scope.

Alternatively you can just free the network resources without the client context itself by calling `lwm2m_network_close()`.

## The network is unstable on a µC

The library needs work to be done periodically (ie. `lwm2m_process()` needs to be called frequently). In other words, don't use `delay()` (see [avoid delay](http://playground.arduino.cc/Code/AvoidDelay)) or anything that might block the code for more than 50ms or so. There is also a known Arduino for ESP8266 issue with `analogRead()`.

## My device resets itself / crashes

You probably run into a memory shortage. The wakaama library is using heap memory
for incoming packets, as well as outgoing packets if `lwm2m_add_server` is called with
the storing flag enabled. Adding a server consumes a bit of heap memory as well.

Make sure to have around 3kb free heap memory available, disable *storing*, limit the added servers.
Block1 type coap blocks consume additional memory, as well as observing/observed resources.

If json is enabled via LWM2M_SUPPORT_JSON, the json encoding/decoding temporarly consumes
heap memory as well while parsing or encoding messages.
