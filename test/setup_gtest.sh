#!/bin/bash
#if [ ! -d "${GTEST_DIR}" ]; then
    mkdir ${GTEST_DIR}
    if [ -d "/usr/src/gtest/" ]; then
        echo "Copy GTest files to ${GTEST_DIR}"
        cp -r /usr/src/gtest/* ${GTEST_DIR}
        cp -r /usr/include/gtest/* ${GTEST_DIR}
    fi
#fi