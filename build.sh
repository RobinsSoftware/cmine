#!/bin/bash
# simple build script

# git submodules
git submodule init
git submodule update

# build dependencies


# build project
cmake
make