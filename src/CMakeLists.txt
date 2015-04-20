
# CMake version
cmake_minimum_required (VERSION 3.0.1)

# Set up compiler definitions
add_definitions(-std=c++0x
                -pthread
                -Wall
                -Wextra)

# Frame
add_subdirectory(frame)

# Test program code
add_subdirectory(frame_test)

