#!/bin/sh -eux

pip install --user platformio

for TESTNAME in ArduinoBuildTest
do
	cd ${TRAVIS_BUILD_DIR}/test/$TESTNAME/
	platformio ci $TESTNAME.ino -l . -l ../../ -b $BOARD
done

