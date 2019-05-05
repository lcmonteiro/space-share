cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceHelper target
# ---------------------------------------------------------
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
# ---------------------------------------------------------
# end
# ---------------------------------------------------------