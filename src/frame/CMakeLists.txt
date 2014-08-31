project(Frame)

cmake_minimum_required (VERSION 3.0.1)

add_definitions(-std=c++0x
                -pthread
                -Wall
                -Wextra)


include_directories(${Frame_SOURCE_DIR}/include,
                    ${Frame_SOURCE_DIR})

add_subdirectory(source)
