# minimum version of cmake
cmake_minimum_required(VERSION 3.10)

# define the project name
project(takeImageFromVideo)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# find the OpenCV package
find_package(OpenCV REQUIRED)

# add the executable
add_executable(takeImageFromVideo main.cpp)

# link the OpenCV libraries
target_link_libraries(takeImageFromVideo ${OpenCV_LIBS})