cmake_minimum_required (VERSION 3.8)
# target
add_library(ShareModule INTERFACE
	#MTransform.cpp
	#MSpliter.cpp
)
# includes
target_include_directories(ShareModule INTERFACE
	.
)
# target dependencies
target_link_libraries(ShareModule 
INTERFACE 
	ShareKernel
	SpaceMonitor
	SpaceResource
	ShareConnector
	ShareFunction
)