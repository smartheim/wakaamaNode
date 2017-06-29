#!/bin/bash -e

: ${VERSION:=1.8.3}
: ${BOARD:=arduino:avr:mega:cpu=atmega1280}
: ${TRAVIS_BUILD_DIR:=$(pwd)}

if [ ! -d ~/arduino-$VERSION ]; then
    mkdir -p ~/arduino-$VERSION
    curl -o arduino.tar.xz -sS http://downloads.arduino.cc/arduino-$VERSION-linux64.tar.xz || die "Failed to download arduino IDE (http://downloads.arduino.cc/arduino-$VERSION-linux64.tar.xz)"
    tar xf arduino.tar.xz --strip 1 -C ~/arduino-$VERSION || die "Failed to extract the arduino package"
fi

if [ ! -d ~/Arduino/libraries ]; then
    mkdir -p ~/Arduino
    mkdir -p ~/Arduino/libraries
fi

if [ ! -d "${TRAVIS_BUILD_DIR}/src" ]; then
    echo "Call this script from the repository root directory!"
    exit 1
fi

if [ ! -d ~/Arduino/libraries/libWakaamaNodes ]; then
    ln -s ${TRAVIS_BUILD_DIR}/src ~/Arduino/libraries/libWakaamaNodes
fi

# cp ${TRAVIS_BUILD_DIR}/examples/arduino_example/wakaama_config.h ~/Arduino/libraries/libWakaamaNodes/wakaama
cp ${TRAVIS_BUILD_DIR}/examples/arduino_example/wakaama_config.h ~/Arduino/libraries/libWakaamaNodes

# We need the time_t type for wakaama
if [ ! -d ~/Arduino/libraries/AVR_Standard_C_Time_Library ]; then
    echo "Install libraries"
    ~/arduino-$VERSION/arduino --install-library "AVR Standard C Time Library"
fi

echo "~/arduino-$VERSION/arduino --verify --board $BOARD ${TRAVIS_BUILD_DIR}/examples/arduino_example/arduino_example.ino"
~/arduino-$VERSION/arduino --verify --board $BOARD ${TRAVIS_BUILD_DIR}/examples/arduino_example/arduino_example.ino
