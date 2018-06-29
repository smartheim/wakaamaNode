# Windows/Linux client example
This example client features the lwm2m **urn:oma:lwm2m:ext:3342** Switch object.
For each screen on the running windows/linux system another instance of the object is created.

It uses the win32 API on windows and the dbus power interface on Linux.

# Features

Shows how to use:

* The object definition C++-API
* The connection C++-API
* The firmware update C++-API
* A predefined object of the lwm2m registry

## Build

Use `cmake` to build this example.
