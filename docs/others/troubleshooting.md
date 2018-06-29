## The network is completely unstable... What's going on?

The library needs work to be done periodically (ie. `lwm2m_process()` needs to be called frequently). In other words, don't use `delay()` (see [avoid delay](http://playground.arduino.cc/Code/AvoidDelay)) or anything that might block the code for more than 50ms or so. There is also a known Arduino for ESP8266 issue with `analogRead()`, see [Limitations and known issues](limitations-and-known-issues.md#adc-readings).

## My device resets itself / crashes

You probably run into a memory shortage. The wakaama library is using heap memory
for incoming packets, as well as outgoing packets if `lwm2m_add_server` is called with
the storing flag enabled. Adding a server consumes heap memory as well.

Make sure to have around 3kb free heap memory available, disable *storing*, limit the added servers.
Block1 type coap blocks consume additional memory as well as observing/observed resources.

If json is enabled via LWM2M_SUPPORT_JSON, the json encoding/decoding temporarly consumes
heap memory as well.
