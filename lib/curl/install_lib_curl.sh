#!/usr/bin/env bash

mkdir -p build
cd build
#echo "brew --prefix curl"
#brew --prefix curl
#echo "brew ls --verbose curl"
#brew ls --verbose curl
# for normal install use following command
cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..
make
sudo make install

cd ../..
