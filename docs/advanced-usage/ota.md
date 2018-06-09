# OTA updates

lwM2M defines a firmware upgrade object. The wakaamaNode library provides two
reference implementations: For the Arduino OTA model and for Posix/Windows binaries.

Find the implementations in the
[<img src="../../assets/github.png" style="width:20px"> src/firmware](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/src/firmware)
directory.


Updating or even checking the version is a server initatiated operation, wakaamaNode
will not perform any checks on its own.

## On Posix/Windows systems

The firmware update object accepts pushed binaries via coap in the default implementation.
The new binary is saved as "new.current_binary_name". As soon as the update resource is executed,
the current binary will be moved to "old.current_binary_name" and the "new.current_binary_name"
takes it place.

The new binary is started with a command line argument "oldpid=PID". It sends a posix signal SIGTERM
to the old binary via the PID and waits for it to finish.

The old binary waits for SIGTERM and terminates if received.
If not received in time (because the new binary has startup problems for example), the old executable
will stay active.

A posix/win32 binary is required to call `void checkIsUpdated(int argc, char** argv)` on startup.

## Arduino OTA

Because memory space is assumed to be limited, the update process accepts a http URI only and does not take
binaries directly via COAP.

The ESP8266 method `ESPhttpUpdate.update("192.168.0.2", 80, "/arduino.bin");` is used.

## OTA security

You should only accept an OTA request, if you are connected to a DTLS secured connection
with an authentificated server.
