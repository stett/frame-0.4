include_directories(${Frame_SOURCE_DIR}/include
                    ${Frame_SOURCE_DIR})

add_library(Frame SHARED Frame.cpp Component.cpp Archive.cpp Children.cpp Parent.cpp)