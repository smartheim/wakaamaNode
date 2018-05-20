#!/bin/sh -eux

pip install --user platformio

: ${TRAVIS_BUILD_DIR:=$(pwd)}

if [ ! -d "${TRAVIS_BUILD_DIR}/src" ]; then
    echo "Call this script from the repository root directory!"
    exit 1
fi

cd ${TRAVIS_BUILD_DIR}/src/examples/nodemcu_with_led_object/
platformio ci main.cpp -l . -l ../../ --project-conf platformio.ini

