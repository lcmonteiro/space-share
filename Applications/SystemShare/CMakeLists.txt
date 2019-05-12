cmake_minimum_required (VERSION 3.8)
# project
project (SystemShare)
# target
create_executable(
TARGET 
	SystemShare
SOURCES
	Source/main.cpp
LINKS
	ShareInterface
)
# dependencies 
target_link_libraries(SystemShare
	PRIVATE pthread
)
