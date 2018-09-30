cmake_minimum_required (VERSION 3.8)
# target
add_library(ShareKernelModule STATIC
	MProcessTransform.cpp
	MProcessYpsilon.cpp
)
# includes
target_include_directories(ShareKernelModule PUBLIC
	.
)
# target dependencies
target_link_libraries(ShareKernelModule 
PRIVATE 
	ShareKernel
PUBLIC
	SpaceKernel
	SpaceMonitor
	SpaceResource
	ShareConnector
	ShareFunction
)