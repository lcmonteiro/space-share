cmake_minimum_required (VERSION 3.8)
# project
project (SystemShare)
# target
add_executable(SystemShare 
	./Source/main.cpp
)
# dependencies 
target_link_libraries(SystemShare
PRIVATE
	ShareInterface
)
