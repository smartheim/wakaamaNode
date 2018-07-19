# Examples

## Linux/Windows custom object (C-API)
This example client provides a custom lwm2m object that shows a logging message on the console window.

Shows how to use:

* The object definition C-API
* The connection C-API
* A custom main loop integration based on select()

Find it in [<img src="../../assets/github.png" style="width:20px"> examples/linux_win_custom_object_c](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/examples/linux_win_custom_object_c).

## Linux/Windows screen control (C++-API)
This example client features the lwm2m **urn:oma:lwm2m:ext:3342** Switch object.
For each screen on the running windows/linux system another instance of the object is created.

It uses the win32 API on windows and the dbus power interface on Linux.

Shows how to use:

* The object definition C++-API
* The connection C++-API
* The firmware update C++-API
* A predefined object of the lwm2m registry

Find it in [<img src="../../assets/github.png" style="width:20px"> examples/linux_win_screen_control](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/examples/linux_win_screen_control).

## NodeMCU/ESP8266 Led control (C++-API)
This example client provides an lwm2m object to switch the led of an esp01/nodemcu on/off.

Shows how to use:

* The object definition C++-API
* The connection C++-API
* The firmware update C++-API
* A predefined object of the lwm2m registry

Find it in [<img src="../../assets/github.png" style="width:20px"> examples/nodemcu_with_led](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/examples/nodemcu_with_led).
