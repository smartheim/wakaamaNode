# Provides WAKAAMA_NODE_DIR and WAKAAMA_SIMPLE_CLIENT_SOURCES variables

include(${CMAKE_CURRENT_LIST_DIR}/wakaama/wakaama.cmake)
set(WAKAAMA_NODE_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB KNOWN_OBJECTS "${WAKAAMA_NODE_DIR}/lwm2mObjects/*.h")
set(PLATFORM_HEADERS
    ${WAKAAMA_NODE_DIR}/lwm2m_connect.h
    ${WAKAAMA_NODE_DIR}/lwm2m_objects.h
    ${WAKAAMA_NODE_DIR}/lwm2m_objects.hpp
    ${WAKAAMA_NODE_DIR}/object_firmware.hpp
    ${WAKAAMA_NODE_DIR}/object_device.h
    ${WAKAAMA_NODE_DIR}/client_debug.h
    ${WAKAAMA_NODE_DIR}/network.h
    ${KNOWN_OBJECTS}
    )

set(PLATFORM_PRIVATE_HEADERS
    ${WAKAAMA_NODE_DIR}/network/network_utils.h
    )

set(PLATFORM_SOURCES
    ${WAKAAMA_NODE_DIR}/network/network_utils.c
    ${WAKAAMA_NODE_DIR}/network/network_utils.h
    )

if(NOT DONT_USE_POSIX)
    list(APPEND PLATFORM_SOURCES
    ${WAKAAMA_NODE_DIR}/platform/platform_posix.c
    ${WAKAAMA_NODE_DIR}/firmware/firmware_posix.cpp
    )
endif()

if(USE_FREERTOS)
    list(APPEND PLATFORM_SOURCES
    ${WAKAAMA_NODE_DIR}/platform/platform_freertos.c
    )
endif()

if(USE_ESP8266)
    list(APPEND PLATFORM_SOURCES
    ${WAKAAMA_NODE_DIR}/platform/platform_esp8266sdk.c
    ${WAKAAMA_NODE_DIR}/firmware/arduinoOTA.cpp
    )
endif()

file(GLOB_RECURSE NETWORK_MBEDTLS_H "${WAKAAMA_NODE_DIR}/network/mbedtls/include/*.h")
file(GLOB NETWORK_MBEDTLS "${WAKAAMA_NODE_DIR}/network/mbedtls/library/*.c")
file(GLOB NETWORK_MBEDTLS_PL "${WAKAAMA_NODE_DIR}/network/mbedtls/platform/*.c")
if(USE_LWIP)
    list(APPEND PLATFORM_SOURCES ${WAKAAMA_NODE_DIR}/network/network_lwip.c
        ${NETWORK_MBEDTLS_H} ${NETWORK_MBEDTLS} ${NETWORK_MBEDTLS_PL})
else()
    list(APPEND PLATFORM_SOURCES ${WAKAAMA_NODE_DIR}/network/network_posix.c
        ${NETWORK_MBEDTLS_H} ${NETWORK_MBEDTLS} ${NETWORK_MBEDTLS_PL})
endif()


set(WAKAAMA_NODE_DIR_INCLUDE_DIRS
    ${WAKAAMA_SOURCES_DIR}
    ${WAKAAMA_NODE_DIR}
    "${WAKAAMA_NODE_DIR}/network/mbedtls/include"
    "${WAKAAMA_NODE_DIR}/platform/")

set(WAKAAMA_NODE_DIR_SOURCES  ${WAKAAMA_SOURCES} ${PLATFORM_HEADERS} ${PLATFORM_SOURCES} ${PLATFORM_PRIVATE_HEADERS}
    ${WAKAAMA_NODE_DIR}/object_device.c
    ${WAKAAMA_NODE_DIR}/object_security.c
    ${WAKAAMA_NODE_DIR}/object_server.c
    ${WAKAAMA_NODE_DIR}/client_debug.c
    ${WAKAAMA_NODE_DIR}/lwm2m_objects_cpp.cpp
    ${WAKAAMA_NODE_DIR}/lwm2m_objects.c
    ${WAKAAMA_NODE_DIR}/lwm2m_connect.c
    )

