
# CMake version
cmake_minimum_required (VERSION 3.0.1)

# Project name
project (FrameTest)

# Set up compiler definitions
add_definitions(-std=c++0x
                -pthread)

# GTest
add_subdirectory(gtest-1.7.0)

# Test program code
add_subdirectory(frame-test)

# Turn on testing
enable_testing()
add_test(FrameTest FrameTest)
