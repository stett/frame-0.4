
# CMake version
cmake_minimum_required (VERSION 3.0.1)

# CMake modules directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Set up compiler definitions
add_definitions(-std=c++0x
                -pthread
                -Wall
                -Wextra)

# GTest
add_subdirectory(gtest-1.7.0)

# Frame
add_subdirectory(frame)

# Test program code
add_subdirectory(frame_test)

# Sandbox program
add_subdirectory(frame_sandbox)
