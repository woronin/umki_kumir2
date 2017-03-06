#!/bin/bash
cp smart_kumir.ini ../../../build/bin
cd ../../../build
#make clean
cmake ../
#bname=`-d /dev/ttyUSB0`
cd src/actors/umki
make
