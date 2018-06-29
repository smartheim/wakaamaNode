cmake_minimum_required (VERSION 3.0)
project (linux_cpp_example)

include(${CMAKE_CURRENT_LIST_DIR}/../../src/src.cmake)

SET(SOURCES
    src/main.cpp
    src/wakaama_config.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${WAKAAMA_NODE_DIR_SOURCES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS} -DPOSIX)
target_include_directories(${PROJECT_NAME} PRIVATE ${WAKAAMA_NODE_DIR_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/src)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
endif()

# Add LWM2M_WITH_LOGS to debug variant
#set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Debug>:LWM2M_WITH_LOGS>)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
