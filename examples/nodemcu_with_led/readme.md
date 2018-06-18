# ESP8266 client example
This example client provides an lwm2m object to switch the led of an esp01/nodemcu on/off.

## Build
Use platformio to build this example (`pio run`).
You just need to call `pio run --target upload` to upload the binary if it is an esp01 with 1MB flash,
otherwise change the board in `platformio.ini` first.
