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

project(TestsCommon)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

SET(REPO_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)
set(TEST_DIR ${REPO_ROOT}/test)
set(LWIP_DIR ${REPO_ROOT}/contrib/lwip/src)

include("${REPO_ROOT}/src/src.cmake")

enable_testing()

## Prepare gtest
set(GTEST_DIR $ENV{GTEST_DIR} CACHE PATH "")
if(EXISTS "${GTEST_DIR}/src/gtest-all.cc")
    set(GTEST_FILES ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
    set(GTEST_INCLUDE_DIRS ${GTEST_DIR} ${GTEST_DIR}/include)
    add_definitions(-DGTEST_HAS_PTHREAD=0)
else()
    find_package(GTest REQUIRED)
    set(GTEST_FILES "")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-gnu-zero-variadic-macro-arguments -Wno-gnu-folding-constant")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

## Prepare for coverage measuring
if(${COVERAGE})
    set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

# All cpp files in this directory are considered testcase files.
file(GLOB TESTS_FILES ${TEST_DIR}/*.cpp ${TEST_DIR}/*.c ${TEST_DIR}/*.h)

file(GLOB_RECURSE HELPER_FILES_LWIP
    ${LWIP_DIR}/api/*.c ${LWIP_DIR}/core/*.c ${LWIP_DIR}/include/*.h ${LWIP_DIR}/netif/*.c
    ${CMAKE_CURRENT_LIST_DIR}/with_lwip/*.c
    ${CMAKE_CURRENT_LIST_DIR}/with_lwip/*.h
    ${CMAKE_CURRENT_LIST_DIR}/helper/*.*)
set(HELPER_INCLUDE_DIRS_LWIP
    "${CMAKE_CURRENT_LIST_DIR}/with_lwip/include"
    "${LWIP_DIR}/include")

file(GLOB_RECURSE HELPER_FILES ${CMAKE_CURRENT_LIST_DIR}/helper/*.*)


add_subdirectory(backward)

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

function(prepare_target PROJECT_NAME)
    add_backward(${PROJECT_NAME})

    target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBUNWIND_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIRS} ${WAKAAMA_NODE_DIR_INCLUDE_DIRS}
        ${HELPER_INCLUDE_DIRS_LWIP} "${CMAKE_CURRENT_LIST_DIR}/helper/" ${TEST_DIR} ${CMAKE_CURRENT_LIST_DIR})
    set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

    # -DLWM2M_WITH_LOGS -DLWIP_DEBUG

    if (UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
    endif()

    if(GTEST_FOUND)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${GTEST_BOTH_LIBRARIES})
    endif()

    add_test(${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
endfunction(prepare_target)

#####################################################################
# Use the Lwip network stack on top of linux tapif or windows pcapif
# instead of the posix sockets library directly
project(TestsWithLwIP CXX C)

add_executable(${PROJECT_NAME} ${TESTS_FILES} ${GTEST_FILES}
    ${WAKAAMA_NODE_DIR_SOURCES} ${HELPER_FILES_LWIP} ${BACKWARD_ENABLE})
prepare_target(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS}
    -DLWM2M_CLIENT_MODE -DLWM2M_SERVER_MODE  -DLWM2M_SUPPORT_JSON
    -DLWIP -DPOSIX -DLWM2M_WITHOUT_ALLOC_FREE
    -DTAP_CLIENT_DEVIDE="${TAP_CLIENT_DEVICE}" -DTAP_CLIENT_ADDR="${TAP_CLIENT_ADDR}"
    -DTAP_SERVER_DEVICE="${TAP_SERVER_DEVICE}" -DTAP_SERVER_ADDR="${TAP_SERVER_ADDR}")

#####################################################################
# Use POSIX sockets API for tests
project(TestsWithPosix CXX C)

add_executable(${PROJECT_NAME} ${TESTS_FILES} ${GTEST_FILES}
    ${WAKAAMA_NODE_DIR_SOURCES} ${HELPER_FILES} ${HELPER_FILES_LWIP} ${BACKWARD_ENABLE})
prepare_target(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS}
    -DLWM2M_CLIENT_MODE -DLWM2M_SERVER_MODE  -DLWM2M_SUPPORT_JSON
    -DLWM2M_WITHOUT_ALLOC_FREE -DLWM2M_NETWORK_LOGGING)
