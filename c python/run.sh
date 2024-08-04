#!/bin/bash

# NOTE: Unless you are using the same OS and python version as me this script will not know where
# the compiled C library is located. If you run this script once you will be able to find the .so
# file in your newly generated build directory. Change the value of build path to be the correct path
# to where your .so file gets generated and run this script again.
build_path="build/lib.linux-x86_64-cpython-38/rhythm.cpython-38-x86_64-linux-gnu.so"

# This tool does not currently have a flag for installing, you can do it manually:
# python3 setup.py install

# Removes the build artifacts.
clean() {
    echo "Removing build artifacts."
    rm *.so > /dev/null 2>&1
    rm -r build > /dev/null 2>&1
}

if [ $# -eq 1 ]; then
    if [ $1 == "clean" ]; then
        clean
        exit 0
    else
        echo "The only arg is 'clean'."
        exit 1
    fi
elif [ $# -eq 0 ]; then
    # Need to remove build dir or it won't compile again.
    clean

    # Build the rhythm.so file and copy it to the present dir.
    python3 setup.py build
    if ! test -f $build_path; then
        echo "ERROR: No compiled .so file found, update build_path at the top of this file with the correct path."
        exit 1
    fi
    cp $build_path rhythm.so

    # Run the demo script.
    python3 demo.py
    exit 0
else
    echo "Too many args."
    exit 1
fi