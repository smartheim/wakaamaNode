## Compile for embedded with lwip network (internally it uses linux tapif or windows pcapif)
## We actually do not use the cmake test system (we would use add_test for each test suite)
## but the gtest framework. We therefore add only "one" test case here, which internally
## performs many gtest testcases.

cmake_minimum_required(VERSION 3.1)

project(Lwm2mCLientLibWithLwIP CXX C)

SET(REPO_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)
set(TEST_DIR ${REPO_ROOT}/test)
set(LWIP_DIR ${REPO_ROOT}/contrib/lwip/src)

include("${REPO_ROOT}/src/wakaama_simple_client.cmake")

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

enable_testing()

## Prepare gtest
if(EXISTS "${GTEST_DIR}")
    set(GTEST_DIR $ENV{GTEST_DIR} CACHE PATH "")
    set(GTEST_FILES ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
    set(GTEST_INCLUDE_DIRS ${GTEST_DIR} ${GTEST_DIR}/include)
    add_definitions(-DGTEST_HAS_PTHREAD=0)
else()
    find_package(GTest REQUIRED)
    set(GTEST_FILES "")
endif()

## Prepare for coverage measuring
if(${COVERAGE})
	set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

# All cpp files in this directory are considered testcase files.
file(GLOB TESTS_FILES ${TEST_DIR}/*.cpp ${TEST_DIR}/*.c ${TEST_DIR}/*.h)

file(GLOB_RECURSE LWIP_FILES ${LWIP_DIR}/api/*.c ${LWIP_DIR}/core/*.c ${LWIP_DIR}/include/*.h ${LWIP_DIR}/netif/*.c ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*.h)

project(Lwm2mClientTestsLWIP CXX)

add_executable(${PROJECT_NAME} ${TESTS_FILES} ${GTEST_FILES} ${WAKAAMA_SIMPLE_CLIENT_SOURCES} ${LWIP_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS} ${WAKAAMA_SIMPLE_CLIENT_INCLUDE_DIRS} ${LWIP_DIR}/include ${TEST_DIR} ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS}
    -DLWM2M_CLIENT_MODE -DLWM2M_SERVER_MODE  -DLWM2M_SUPPORT_JSON
#    -DLWM2M_WITH_LOGS
#    -DWITH_LOGS
    -DLWIP
    -DTAP_CLIENT_DEVIDE="${TAP_CLIENT_DEVICE}" -DTAP_CLIENT_ADDR="${TAP_CLIENT_ADDR}"
    -DTAP_SERVER_DEVICE="${TAP_SERVER_DEVICE}" -DTAP_SERVER_ADDR="${TAP_SERVER_ADDR}")

if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

if(NOT EXISTS "${GTEST_DIR}")
    target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
endif()

add_test(${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

