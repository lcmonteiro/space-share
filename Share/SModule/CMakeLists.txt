cmake_minimum_required (VERSION 3.8)
# target
add_library(ShareModule STATIC
	#MTransform.cpp
	MYpsilon.cpp
)
# includes
target_include_directories(ShareModule PUBLIC
	.
)
# target dependencies
target_link_libraries(ShareModule 
PRIVATE 
	ShareKernel
PUBLIC
	SpaceMonitor
	SpaceResource
	ShareConnector
	ShareFunction
)