#!/bin/bash

cd build &&
cmake ../src &&
make &&
./frame_test/FrameTest