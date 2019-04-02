cmake_minimum_required (VERSION 3.8)
# SpaceShare target
add_library(SpaceHelper 
STATIC
	SBase64.cpp
	SHash.cpp
)
# includes
target_include_directories(SpaceHelper 
PUBLIC
	.
)
# target dependencies
target_link_libraries(SpaceHelper 
PUBLIC 
	SpaceKernel
	SpaceResource
)