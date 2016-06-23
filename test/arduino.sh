#!/bin/bash -eux

/sbin/start-stop-daemon --start --quiet --pidfile /tmp/custom_xvfb_1.pid --make-pidfile --background --exec /usr/bin/Xvfb -- :1 -ac -screen 0 1280x1024x16
sleep 3
export DISPLAY=:1.0

if [ ! -d ~/arduino-$VERSION ]; then
    mkdir -p ~/arduino-$VERSION
    curl -sS http://downloads.arduino.cc/arduino-$VERSION-linux64.tar.xz | tar xJ -C ~/arduino-$VERSION --strip 1 ||
    curl -sS http://downloads.arduino.cc/arduino-$VERSION-linux64.tgz | tar xz -C ~/arduino-$VERSION --strip 1 
fi

if [ ! -d ~/Arduino/libraries ]
    mkdir -p ~/Arduino
    mkdir -p ~/Arduino/libraries
fi

export PATH=$PATH:~/arduino-$VERSION/

cd ${TRAVIS_BUILD_DIR}/src
ln -s $PWD ~/Arduino/libraries/libWakaamaNodes

for TESTNAME in ArduinoBuildTest
do
        arduino --verify --board $BOARD ${TRAVIS_BUILD_DIR}/test/$TESTNAME/$TESTNAME.ino
done

