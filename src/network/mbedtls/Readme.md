
# mbedTLS and patches for ESP8266

This library replaces the integrated mbedTLS library that is integrated into the original ESP8266 SDK (NON OS and RTOS).

This is an updated and upgraded version. mbedTLS base was 2.5.0 but some patches have been integrated.

See the original repository that was taken from the official mbedTLS development branch here: https://github.com/dunkelstern/mbedtls

Integrated patches so far, see below for sources:

- HKDF (**H**MAC based **K**ey **D**erivation **F**unction)
- AEAD ChaCha20 + Poly1305
- ED25519
- SRP (**S**ecure **R**emote **P**assword)

## Building

Some pointers:

1. Get the ESP8266 compiler: https://github.com/pfalcon/esp-open-sdk
2. Get the SDK
3. Unpack SDK somewhere
4. Set up the environment
    ```bash
    export PATH="/path/to/compiler/xtensa-lx106-elf/bin:$PATH"
    export SDK_PATH="$HOME/esp-sdk/ESP8266_RTOS_SDK"
    export BIN_PATH="$HOME/esp-sdk/build"

    export CFLAGS="-I${SDK_PATH}/include -I${SDK_PATH}/extra_include $CFLAGS"
    export LDFLAGS="-L${SDK_PATH}/lib $LDFLAGS"
    ```
5. Switch to the base directory and run `make`
6. Grab the library from `.output/lib/libmbedtls.a`
7. Grab the headers from `include/*.h`

If you want to enable or disable some functionality of mbedTLS open `platform/config_esp.h` and set yourself up.

## Legal

### mbedTLS

Cloned from https://github.com/ARMmbed/mbedtls

License: Apache License 2.0 (see LICENSE-Apache-2.0.txt)

### Platform integration code

From the ESP8266 SDK: https://github.com/espressif/ESP8266_RTOS_SDK

Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
Additions Copyright (C) 2015 Angus Gratton

License: Apache License 2.0 (see LICENSE-Apache-2.0.txt)

### HKDF 

Integrated patches from: https://github.com/thomas-fossati/mbedtls

License: Apache License 2.0 (see LICENSE-Apache-2.0.txt)

### AEAD ChaCha20 + Poly1305 

Integrated patches from: https://github.com/damaki/mbedtls/tree/chacha20

License: Apache License 2.0 (see LICENSE-Apache-2.0.txt)

### ED25519

Integrated patches from: https://github.com/VirgilSecurity/mbedtls/tree/virgil-security-ed25519

License: Apache License 2.0 (see LICENSE-Apache-2.0.txt)

### SRP (Secure Remote Password)

Original Repository: https://github.com/cocagne/csrp

Conversion to mbedTLS: https://github.com/dwimberger/mbedtls-csrp

Patches by:

- https://github.com/ksjoberg/csrp.git
- https://github.com/damv/mbedtls-csrp
- https://github.com/dunkelstern/mbedtls-csrp

License: MIT (see LICENSE-MIT.txt)

