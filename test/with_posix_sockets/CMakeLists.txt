## Compile for posix with posix sockets
## We actually do not use the cmake test system (we would use add_test for each test suite)
## but the gtest framework. We therefore add only "one" test case here, which internally
## performs many gtest testcases.

cmake_minimum_required(VERSION 3.1)
project(Lwm2mClientTests CXX C)

SET(REPO_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)
set(TEST_DIR ${REPO_ROOT}/test)

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

## Prepare for coverage measuring
if(${COVERAGE})
	set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

# All cpp files in this directory are considered testcase files.
file(GLOB TESTS_FILES ${TEST_DIR}/*.cpp ${TEST_DIR}/*.c ${TEST_DIR}/*.h)

add_executable(${PROJECT_NAME} ${TESTS_FILES} ${GTEST_FILES} ${CMAKE_CURRENT_LIST_DIR}/posix_network_helper.c ${TEST_DIR}/network_helper.h ${WAKAAMA_SIMPLE_CLIENT_SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS} ${WAKAAMA_SIMPLE_CLIENT_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${WAKAAMA_DEFINITIONS} -DLWM2M_CLIENT_MODE -DLWM2M_SERVER_MODE  -DLWM2M_SUPPORT_JSON)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

add_test(${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

if(GTEST_FOUND)
    target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
endif()

