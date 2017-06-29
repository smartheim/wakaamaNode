## We actually do not use the cmake test system (we would use add_test for each test suite)
## but the gtest framework. We therefore add only "one" test case here, which internally
## performs many gtest testcases.
##
## Each c++ source file in this directory is a testsuite. 
##
## if USE_LWIP is diabled (-DUSE_LWIP=OFF):
## Compile for posix with posix sockets
##
## if USE_LWIP is enabled (-DUSE_LWIP=ON):
## Compile with lwip network (internally it uses linux tapif or windows pcapif)

cmake_minimum_required(VERSION 3.1)

project(Lwm2mCLientLibWithLwIP CXX C)

option(USE_LWIP "Use the Lwip network stack on top of linux tapif or windows pcapif instead of the posix sockets library directly" OFF)

SET(REPO_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)
set(TEST_DIR ${REPO_ROOT}/test)
set(LWIP_DIR ${REPO_ROOT}/contrib/lwip/src)

include("${REPO_ROOT}/src/wakaama_simple_client.cmake")

enable_testing()

## Prepare gtest
if(EXISTS "${GTEST_DIR}/src/gtest-all.cc")
    set(GTEST_DIR $ENV{GTEST_DIR} CACHE PATH "")
    set(GTEST_FILES ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
    set(GTEST_INCLUDE_DIRS ${GTEST_DIR} ${GTEST_DIR}/include)
    add_definitions(-DGTEST_HAS_PTHREAD=0)
else()
    find_package(GTest REQUIRED)
    set(GTEST_FILES "")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

## Prepare for coverage measuring
if(${COVERAGE})
	set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

# All cpp files in this directory are considered testcase files.
file(GLOB TESTS_FILES ${TEST_DIR}/*.cpp ${TEST_DIR}/*.c ${TEST_DIR}/*.h)
if (USE_LWIP)
    file(GLOB_RECURSE AUX_FILES ${LWIP_DIR}/api/*.c ${LWIP_DIR}/core/*.c ${LWIP_DIR}/include/*.h ${LWIP_DIR}/netif/*.c
        ${CMAKE_CURRENT_LIST_DIR}/with_lwip/*.c ${CMAKE_CURRENT_LIST_DIR}/with_lwip/*.h
        ${CMAKE_CURRENT_LIST_DIR}/aux/*.*)
    set(AUX_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/with_lwip" "${LWIP_DIR}/include" "${CMAKE_CURRENT_LIST_DIR}/aux/")
else()
    file(GLOB_RECURSE AUX_FILES ${CMAKE_CURRENT_LIST_DIR}/aux/*.*)
    set(AUX_FILES ${AUX_FILES} ${CMAKE_CURRENT_LIST_DIR}/with_posix_sockets/posix_network_helper.c)
    set(AUX_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/aux/")
endif()

add_executable(${PROJECT_NAME} ${TESTS_FILES} ${GTEST_FILES} ${WAKAAMA_SIMPLE_CLIENT_SOURCES} ${AUX_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS} ${WAKAAMA_SIMPLE_CLIENT_INCLUDE_DIRS} ${AUX_INCLUDE_DIRS} ${TEST_DIR} ${CMAKE_CURRENT_LIST_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

# -DLWM2M_WITH_LOGS -DLWIP_DEBUG
if (USE_LWIP)
    if (NOT DEFINED TAP_SERVER_ADDR)
        set(TAP_SERVER_ADDR "192.168.7.2")
    endif()
    if (NOT DEFINED TAP_CLIENT_ADDR)
        set(TAP_CLIENT_ADDR "192.168.7.1")
    endif()
    if (NOT DEFINED TAP_CLIENT_DEVICE)
        set(TAP_CLIENT_DEVICE "tap0")
    endif()
    if (NOT DEFINED TAP_SERVER_DEVICE)
        set(TAP_SERVER_DEVICE "tap1")
    endif()

    target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS}
        -DLWM2M_CLIENT_MODE -DLWM2M_SERVER_MODE  -DLWM2M_SUPPORT_JSON
        -DLWIP
        -DTAP_CLIENT_DEVIDE="${TAP_CLIENT_DEVICE}" -DTAP_CLIENT_ADDR="${TAP_CLIENT_ADDR}"
        -DTAP_SERVER_DEVICE="${TAP_SERVER_DEVICE}" -DTAP_SERVER_ADDR="${TAP_SERVER_ADDR}")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS}
        -DLWM2M_CLIENT_MODE -DLWM2M_SERVER_MODE  -DLWM2M_SUPPORT_JSON)
endif()

if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

if(GTEST_FOUND)
    target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
endif()

add_test(${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
