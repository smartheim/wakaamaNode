# Provides WAKAAMA_NODE_DIR and WAKAAMA_SIMPLE_CLIENT_SOURCES variables

include(${CMAKE_CURRENT_LIST_DIR}/wakaama/wakaama.cmake)
set(WAKAAMA_NODE_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB KNOWN_OBJECTS "${WAKAAMA_NODE_DIR}/include/lwm2mObjects/*.h")
set(HEADERS
    ${WAKAAMA_NODE_DIR}/include/lwm2m/context.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/c_connect.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/connect.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/server.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/c_objects.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/objects.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/firmware.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/object_device.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/debug.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/network.h
    ${WAKAAMA_NODE_DIR}/include/lwm2m/events.h
    ${KNOWN_OBJECTS}
    )

set(PRIVATE_HEADERS
    ${WAKAAMA_NODE_DIR}/internal_objects.h
    ${WAKAAMA_NODE_DIR}/macro_helper.h
    ${WAKAAMA_NODE_DIR}/inplace_function.h
    )

set(PLATFORM_SOURCES "")

file(GLOB_RECURSE NETWORK_MBEDTLS_H "${WAKAAMA_NODE_DIR}/network/mbedtls/include/*.h")
file(GLOB NETWORK_MBEDTLS "${WAKAAMA_NODE_DIR}/network/mbedtls/library/*.c")
file(GLOB NETWORK_MBEDTLS_PL "${WAKAAMA_NODE_DIR}/network/mbedtls/platform/*.c")
list(APPEND PLATFORM_SOURCES
    ${WAKAAMA_NODE_DIR}/network/server_ssl.c
    ${WAKAAMA_NODE_DIR}/network/network_ssl.c
    ${WAKAAMA_NODE_DIR}/network/network_common.c
    ${WAKAAMA_NODE_DIR}/network/network_common.h
    ${WAKAAMA_NODE_DIR}/platform/platform_posix.c
    ${WAKAAMA_NODE_DIR}/firmware/firmware_posix.cpp
    ${WAKAAMA_NODE_DIR}/platform/platform_freertos.c
    ${WAKAAMA_NODE_DIR}/platform/platform_esp8266sdk.c
    ${WAKAAMA_NODE_DIR}/firmware/arduinoOTA.cpp
    ${WAKAAMA_NODE_DIR}/network/network_lwip.c ${WAKAAMA_NODE_DIR}/network/network_posix.c
    ${WAKAAMA_NODE_DIR}/network/network_lwip.h ${WAKAAMA_NODE_DIR}/network/network_posix.h
    ${NETWORK_MBEDTLS_H} ${NETWORK_MBEDTLS} ${NETWORK_MBEDTLS_PL})


set(WAKAAMA_NODE_DIR_INCLUDE_DIRS
    ${WAKAAMA_SOURCES_DIR}
    "${WAKAAMA_NODE_DIR}/include"
    "${WAKAAMA_NODE_DIR}/network/mbedtls/include")

set(WAKAAMA_NODE_DIR_SOURCES
    ${WAKAAMA_SOURCES}
    ${HEADERS}
    ${PRIVATE_HEADERS}
    ${PLATFORM_SOURCES}
    ${WAKAAMA_NODE_DIR}/object_device.c
    ${WAKAAMA_NODE_DIR}/object_security.c
    ${WAKAAMA_NODE_DIR}/object_server.c
    ${WAKAAMA_NODE_DIR}/client_debug.c
    ${WAKAAMA_NODE_DIR}/objects.cpp
    ${WAKAAMA_NODE_DIR}/c_objects.c
    ${WAKAAMA_NODE_DIR}/c_connect.c
    ${WAKAAMA_NODE_DIR}/connect.cpp
    ${WAKAAMA_NODE_DIR}/events.cpp
    )

