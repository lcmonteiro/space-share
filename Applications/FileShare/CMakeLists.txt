cmake_minimum_required (VERSION 3.0)
#
project (FileShare)
#
add_executable(FileShare 
	./Source/main.cpp
	$<TARGET_OBJECTS:SpaceKernel>
	$<TARGET_OBJECTS:ShareInterface>
)
# 
target_link_libraries(FileShare 
PRIVATE
)
