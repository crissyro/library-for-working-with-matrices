#!/bin/bash
# Script to run tests

cd build || exit
make test
cd ..
