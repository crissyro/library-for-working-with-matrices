#!/bin/bash
# Build script for the Matrix Library

mkdir -p build
cd build || exit
cmake ..
make
cd ..