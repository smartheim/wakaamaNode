# Provides WAKAAMA_SIMPLE_CLIENT_DIR and WAKAAMA_SIMPLE_CLIENT_SOURCES variables

include(${CMAKE_CURRENT_LIST_DIR}/wakaama/wakaama.cmake)
set(WAKAAMA_SIMPLE_CLIENT_DIR ${CMAKE_CURRENT_LIST_DIR})

set(WAKAAMA_SIMPLE_CLIENT_INCLUDE_DIRS ${WAKAAMA_SOURCES_DIR} ${WAKAAMA_SIMPLE_CLIENT_DIR})

set(PLATFORM_HEADERS
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_firmware.h
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_client_debug.h
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_network.h
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_simple_client.h
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_device_data.h
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_object_utils.h
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_network.h
    )

set(PLATFORM_PRIVATE_HEADERS
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/network/network_utils.h
    )

set(PLATFORM_SOURCES
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/platform/posix.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/platform/esp8266sdk.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/platform/freertos.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/firmware/esp8266sdk.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/network/posix_network.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/network/lwip_network.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/network/network_utils.c
    )

set(WAKAAMA_SIMPLE_CLIENT_SOURCES  ${WAKAAMA_SOURCES} ${PLATFORM_HEADERS} ${PLATFORM_SOURCES} ${PLATFORM_PRIVATE_HEADERS}
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/object_device.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/object_security.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/object_server.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_client_debug.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_object_utils.c
    ${WAKAAMA_SIMPLE_CLIENT_DIR}/wakaama_simple_client.c
    )

