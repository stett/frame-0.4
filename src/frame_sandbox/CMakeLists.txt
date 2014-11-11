
# Project Name
project(FrameSandbox)

# Find packaes
find_package(SFML 2 REQUIRED system window graphics) #// network audio)

# Includes
include_directories(${SFML_INCLUDE_DIR})
include_directories(${FrameSandbox_SOURCE_DIR})
include_directories(${Frame_SOURCE_DIR}/include)

# Define the executable
add_executable(FrameSandbox main.cpp)

# Make links
target_link_libraries(FrameSandbox Frame ${SFML_LIBRARIES})
