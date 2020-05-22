#!/bin/bash

CMAKE_BIN_DIR='cmake-build-debug'

for file in *; do
    if [[ -d $file && $file != $CMAKE_BIN_DIR ]]; then
        pushd $file > /dev/null
        ls -1 *.c | awk -F'.' '{print "add_executable(" $1 " " $0 ")"}' > CMakeLists.txt
        ls -1 *.txt |grep -v 'CMakeLists'| awk '{print "FILE(COPY " $0 " DESTINATION ${CMAKE_CURRENT_BINARY_DIR})"}' >> CMakeLists.txt
        popd > /dev/null
    fi
done
