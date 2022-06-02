#!/bin/bash
# simple build script

# git submodules
git submodule init
git submodule update

# build & install dependencies
cd dependencies/json-c
mkdir build
mkdir json-c-install
cd build
cmake -D CMAKE_INSTALL_PREFIX=../json-c-install CMAKE_MACOSX_RPATH=1 ../
make
make test
make install
cd ../../../

# build project
cmake ./ 
make