#!/bin/bash -eux

: ${GTEST_DIR:=~/gtest}

# GTest files
if [ ! -d "${GTEST_DIR}" ]; then
    mkdir ${GTEST_DIR}
    if [ -d "/usr/src/gtest/" ]; then
        cp -r /usr/src/gtest/* ${GTEST_DIR}
    fi
fi

# Remove 
sudo brctl delbr tap0tap1
sudo ip a del dev tap0 192.168.7.1/24
sudo ip a del dev tap1 192.168.7.2/24
sudo ip tuntap del dev tap0 mode tap
sudo ip tuntap del dev tap1 mode tap

# Add
sudo ip tuntap add dev tap0 mode tap user $(id -u)
sudo ip tuntap add dev tap1 mode tap user $(id -u)
sudo ip a a dev tap0 192.168.7.1/24
sudo ip a a dev tap1 192.168.7.2/24

sudo brctl addbr tap0tap1
sudo brctl addif tap0tap1 tap0
sudo brctl addif tap0tap1 tap1

# Activate
sudo ifconfig tap0tap1 up
sudo ifconfig tap0 up
sudo ifconfig tap1 up

: ${TRAVIS_BUILD_DIR:=$(pwd)}

if [ ! -d "${TRAVIS_BUILD_DIR}/src" ]; then
    echo "Call this script from the repository root directory!"
    exit 1
fi

# Create a build dir and change to that.
if [ ! -d "${TRAVIS_BUILD_DIR}/buildtestlwip" ]; then
    mkdir ${TRAVIS_BUILD_DIR}/buildtestlwip
fi
cd ${TRAVIS_BUILD_DIR}/buildtestlwip

CTEST_OUTPUT_ON_FAILURE=1
cmake -DTAP_CLIENT_DEVICE="tap0" -DTAP_SERVER_DEVICE="tap1" -DTAP_SERVER_ADDR="192.168.7.2" -DTAP_CLIENT_ADDR="192.168.7.1" -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER -DCMAKE_C_COMPILER=$CMAKE_C_COMPILER -DGTEST_DIR="${GTEST_DIR}" ${TRAVIS_BUILD_DIR}/test/with_lwip
make 
make test

cd ${TRAVIS_BUILD_DIR}

# Remove 
sudo brctl delbr tap0tap1
sudo ip a del dev tap0 192.168.7.1/24
sudo ip a del dev tap1 192.168.7.2/24
sudo ip tuntap del dev tap0 mode tap
sudo ip tuntap del dev tap1 mode tap

