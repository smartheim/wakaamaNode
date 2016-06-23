#!/bin/bash -eux

export PATH=${TRAVIS_BUILD_DIR}/cmake/bin:${PATH}

# GTest files
if [ ! -d "${GTEST_DIR}" ]; then
    mkdir ${GTEST_DIR}
fi
cp -r /usr/src/gtest/* ${GTEST_DIR}

sudo ip tuntap add dev tap0 mode tap user $(id -u)
sudo ip tuntap add dev tap1 mode tap user $(id -u)
sudo ip a a dev tap0 192.168.7.1/24
sudo ip a a dev tap1 192.168.7.2/24

sudo brctl addbr tap0tap1
sudo brctl addif tap0tap1 tap0
sudo brctl addif tap0tap1 tap1


# Create a build dir and change to that.
if [ ! -d "${TRAVIS_BUILD_DIR}/buildtest" ]; then
    mkdir ${TRAVIS_BUILD_DIR}/buildtest
fi
cd ${TRAVIS_BUILD_DIR}/buildtest

# Execute cmake and build and test.
cmake -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER -DGTEST_DIR="${GTEST_DIR}" ${TRAVIS_BUILD_DIR}/test/with_posix_sockets
make 
make test
rm -rf ${TRAVIS_BUILD_DIR}/buildtest/*

cmake -DTAP_CLIENT_DEVICE="tap0" -DTAP_SERVER_DEVICE="tap1" -DTAP_SERVER_ADDR="192.168.7.2" -DTAP_CLIENT_ADDR="192.168.7.1" -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER -DGTEST_DIR="${GTEST_DIR}" ${TRAVIS_BUILD_DIR}/test/with_lwip
make 
make test

cd ${TRAVIS_BUILD_DIR}

sudo brctl delbr tap0tap1
sudo ip a del dev tap0 192.168.7.1/24
sudo ip a del dev tap1 192.168.7.2/24
sudo ip tuntap del dev tap0 mode tap
sudo ip tuntap del dev tap1 mode tap
