cmake_minimum_required (VERSION 3.8)
# folder for core objects
add_subdirectory(SCodecV1)
# folder for module
add_subdirectory(SModule)
# SpaceShare target
add_library(ShareKernel STATIC
	SConnector.cpp
)
# includes
target_include_directories(ShareKernel 
PUBLIC
	.
)
# target dependencies
target_link_libraries(ShareKernel 
PUBLIC
	SpaceKernel
PRIVATE 
	ShareKernelCodec
	ShareKernelModule
)