#!/bin/bash
if [ ! -d "${GTEST_DIR}" ]; then
    mkdir ${GTEST_DIR}
    if [ -d "/usr/src/gtest/" ]; then
        cp -r /usr/src/gtest/* ${GTEST_DIR}
    fi
fi