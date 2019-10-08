cmake_minimum_required (VERSION 3.0)
#
project (FileShare)
#
add_executable(FileShare 
	./Source/main.cpp
)
# 
target_link_libraries(FileShare 
PRIVATE
	ShareInterface
	SpaceKernel
)
