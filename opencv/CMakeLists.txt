cmake_minimum_required(VERSION 3.23)
PROJECT (OPENCV)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
#include_directories(/usr/include/opencv4)
ADD_EXECUTABLE(opencvtask main.cpp)
target_link_libraries(opencvtask ${OpenCV_LIBS})