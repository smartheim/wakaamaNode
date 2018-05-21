cmake_minimum_required (VERSION 2.8.3)

project (wakaama_simple_client_linux_example)

include(${CMAKE_CURRENT_LIST_DIR}/../../src/wakaama_simple_client.cmake)

add_definitions(-DLWM2M_CLIENT_MODE)
add_definitions(${WAKAAMA_DEFINITIONS})


include_directories (${WAKAAMA_SOURCES_DIR} ${WAKAAMA_SIMPLE_CLIENT_INCLUDE_DIRS} src/)

SET(SOURCES
    src/main.c
    src/screen_object.c
    src/screen_object.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${WAKAAMA_SIMPLE_CLIENT_SOURCES})

# Add LWM2M_WITH_LOGS to debug variant
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Debug>:LWM2M_WITH_LOGS>)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

