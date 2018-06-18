#!/bin/bash -e
# -e: cmd1 && cmd2 && cmd3 === set -e \n cmd1 \n cmd2 \n cmd3
# -u: shell prints a message to stderr when it tries to expand a variable that is not set
# -x: The shell prints each command in a script to stderr before running it

: ${TRAVIS_BUILD_DIR:=$PWD}
: ${GTEST_DIR:=}
: ${CMAKE_C_COMPILER:=gcc}
: ${CMAKE_CXX_COMPILER:=g++}

# Create a build dir and change to that.
rm -rf ${TRAVIS_BUILD_DIR}/buildtest/*
if [ ! -d "${TRAVIS_BUILD_DIR}/buildtest" ]; then
    mkdir ${TRAVIS_BUILD_DIR}/buildtest
fi
cd ${TRAVIS_BUILD_DIR}/buildtest

# Execute cmake and build and test.
CTEST_OUTPUT_ON_FAILURE=1
cmake --output-on-failure -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER -DCMAKE_C_COMPILER=$CMAKE_C_COMPILER -DGTEST_DIR="${GTEST_DIR}" ${TRAVIS_BUILD_DIR}/test
make -j
RESULT=0

./TestsWithPosix | GREP_COLOR='01;32' grep "^\[.*" || RESULT=1

if [ "${USE_LWIP}" == "OFF" ]; then
    make test || RESULT=1
fi

rm -rf ${TRAVIS_BUILD_DIR}/buildtest/*
cd ${TRAVIS_BUILD_DIR}

exit $RESULT
