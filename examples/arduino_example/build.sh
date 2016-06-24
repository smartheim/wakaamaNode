#!/bin/bash -eux

# We do not support the Arduino IDE right now, we need a feature to allow a library to define
# compiler flags (like LWM2M_CLIENT_MODE).
exit 0

if [ -z ${DISPLAY} ]; then
    /sbin/start-stop-daemon --start --quiet --pidfile /tmp/custom_xvfb_1.pid --make-pidfile --background --exec /usr/bin/Xvfb -- :1 -ac -screen 0 1280x1024x16
    sleep 3
    export DISPLAY=:1.0
fi

if [ ! -d ~/arduino-$VERSION ]; then
    mkdir -p ~/arduino-$VERSION
    curl -sS http://downloads.arduino.cc/arduino-$VERSION-linux64.tar.xz | tar xJ -C ~/arduino-$VERSION --strip 1 ||
    curl -sS http://downloads.arduino.cc/arduino-$VERSION-linux64.tgz | tar xz -C ~/arduino-$VERSION --strip 1 
fi

if [ ! -d ~/Arduino/libraries ]; then
    mkdir -p ~/Arduino
    mkdir -p ~/Arduino/libraries
fi

#export PATH=$PATH:~/arduino-$VERSION/

: ${TRAVIS_BUILD_DIR:=$(pwd)}

if [ ! -d "${TRAVIS_BUILD_DIR}/src" ]; then
    echo "Call this script from the repository root directory!"
    exit 1
fi

if [ ! -d ~/Arduino/libraries/libWakaamaNodes ]; then
    ln -s ${TRAVIS_BUILD_DIR}/src ~/Arduino/libraries/libWakaamaNodes
fi

# We need the time_t type for wakaama
if [ ! -d ~/Arduino/libraries/AVR_Standard_C_Time_Library ]; then
    ~/arduino-$VERSION/arduino --install-library "AVR Standard C Time Library"
fi

~/arduino-$VERSION/arduino --verify --board $BOARD ${TRAVIS_BUILD_DIR}/examples/arduino_example/arduino_example.ino

