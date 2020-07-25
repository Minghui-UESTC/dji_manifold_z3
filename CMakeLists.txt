cmake_minimum_required(VERSION 2.8)
project(readimage)
add_definitions(-std=c++11)
find_package(OpenCV REQUIRED)
add_executable(readimage readimage.cpp)
target_link_libraries(readimage ${OpenCV_LIBS} dcam)

