cmake_minimum_required (VERSION 2.8.11)
#
project (SystemShare)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
# include directories
include_directories(../../Space ../../Share)
# 
add_subdirectory(../../Space)
#
add_subdirectory(../../Share)

