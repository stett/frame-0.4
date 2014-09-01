include_directories(${Frame_SOURCE_DIR}/include
                    ${Frame_SOURCE_DIR})

add_library(Frame Frame.cpp Children.cpp Parent.cpp)