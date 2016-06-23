#!/bin/bash -eux

export PATH=${TRAVIS_BUILD_DIR}/cmake/bin:${PATH}

# GTest files
if [ ! -d "${GTEST_DIR}" ]; then
    mkdir ${GTEST_DIR}
fi
cp -r /usr/src/gtest/* ${GTEST_DIR}

# Create a build dir and change to that.
if [ ! -d "${TRAVIS_BUILD_DIR}/buildtest" ]; then
    mkdir ${TRAVIS_BUILD_DIR}/buildtest
fi
cd ${TRAVIS_BUILD_DIR}/buildtest

# Execute cmake and build and test.
CTEST_OUTPUT_ON_FAILURE=1
cmake -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER -DCMAKE_C_COMPILER=$CMAKE_C_COMPILER  -DGTEST_DIR="${GTEST_DIR}" ${TRAVIS_BUILD_DIR}/test/with_posix_sockets
make 
make test
rm -rf ${TRAVIS_BUILD_DIR}/buildtest/*

cd ${TRAVIS_BUILD_DIR}

