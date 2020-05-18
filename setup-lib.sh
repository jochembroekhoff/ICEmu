#!/bin/bash

git submodule update --init --recursive

pushd lib

pushd unicorn
echo "Build unicorn"
UNICORN_ARCHS="arm" UNICORN_QEMU_FLAGS="--python=/usr/bin/python2" ./make.sh
popd

pushd capstone
echo "Build capstone"
CAPSTONE_ARCHS="arm" ./make.sh
popd

pushd jsoncpp
echo "Build jsoncpp"
mkdir -p build
pushd build
cmake ../
make -j4
popd
popd

popd

