#!/bin/sh
./autogen.sh
./configure --prefix=$HOME/doggy
make clean
make install
