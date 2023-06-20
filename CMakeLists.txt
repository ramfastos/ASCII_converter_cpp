cmake_minimum_required(VERSION 3.23)
project(ASCII_converter_cpp)

set(CMAKE_CXX_STANDARD 23)
set(ENV{OPENCV_DIR} "C:\\opencv\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ASCII_converter_cpp ASCII_converter.cpp)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(ASCII_converter_cpp ${OpenCV_LIBS})