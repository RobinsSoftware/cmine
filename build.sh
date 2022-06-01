#!/bin/bash
# simple build script

# git submodules
git submodule init
git submodule update

# build dependencies
cd dependencies/json-c
cmake ./ -DBUILD_SHARED_LIBS=OFF
cd ../../

# build project
cmake ./
make