
# Include the frame hpp files
include_directories("${PROJECT_SOURCE_DIR}")

# Get the external components directory
#set(PROJECT_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/../ext")

# Include external library headers
#include_directories("${PROJECT_EXTERNAL_DIR}/include")


####
include_directories(${gtest_SOURCE_DIR}/include
                    ${gtest_SOURCE_DIR})
####


# Define the executable test program
add_executable(FrameTest main.cpp)

# Link to external libraries
#target_link_libraries(FrameTest "${PROJECT_EXTERNAL_DIR}/lib/libgtest.a"
#                                "${PROJECT_EXTERNAL_DIR}/lib/libgtest_main.a")

target_link_libraries(FrameTest gtest gtest_main)
