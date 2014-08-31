
# Include everything
include_directories(${FrameTest_SOURCE_DIR})

include_directories(${Frame_SOURCE_DIR}/include)

include_directories(${gtest_SOURCE_DIR}/include
                    ${gtest_SOURCE_DIR})

# Define the executable test program
add_executable(FrameTest main.cpp)

# Link everything to the FrameTest executable
target_link_libraries(FrameTest Frame gtest gtest_main)
