#!/bin/sh -eux

# Download newer version of cmake. We need 3.1 at least, travis provides 2.8.
CMAKE_URL="http://cmake.org/files/v3.3/cmake-3.3.1-Linux-x86_64.tar.gz"
mkdir cmake
curl -L ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake
export PATH=${TRAVIS_BUILD_DIR}/cmake/bin:${PATH}

# GTest files
mkdir ${GTEST_DIR}
cp -r /usr/src/gtest/* ${GTEST_DIR}

USER_ID = $(id -u)
sudo ip tuntap add dev tap0 mode tap user ${USER_ID}
sudo ip tuntap add dev tap1 mode tap user ${USER_ID}
sudo ip a a dev tap0 192.168.7.1/24
sudo ip a a dev tap1 192.168.7.2/24

sudo brctl addbr tap0tap1
sudo brctl addif tap0tap1 tap0
sudo brctl addif tap0tap1 tap1


# Create a build dir and change to that.
mkdir ${TRAVIS_BUILD_DIR}/buildtest
cd ${TRAVIS_BUILD_DIR}/buildtest

# Execute cmake and build and test.
cmake -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER ${TRAVIS_BUILD_DIR}/test/with_posix_sockets
make 
make test
rm-rf *

cmake -DTAP_CLIENT_DEVICE="tap0" -DTAP_SERVER_DEVICE="tap1" -DTAP_SERVER_ADDR="192.168.7.2" -DTAP_CLIENT_ADDR="192.168.7.1" -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER ${TRAVIS_BUILD_DIR}/test/with_lwip
make 
make test

cd ${TRAVIS_BUILD_DIR}

sudo brctl delbr tap0tap1
sudo ip a del dev tap0 192.168.7.1/24
sudo ip a del dev tap1 192.168.7.2/24
sudo ip tuntap del dev tap0 mode tap
sudo ip tuntap del dev tap1 mode tap
