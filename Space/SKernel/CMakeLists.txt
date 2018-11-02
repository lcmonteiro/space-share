cmake_minimum_required (VERSION 3.8)
# folder for core objects
add_subdirectory(SLinux)
# SpaceShare target
add_library(SpaceKernel 
STATIC
	SAddress.cpp
	SBase64.cpp
	SContainer.cpp
	SHash.cpp
	SLog.cpp
)
# includes
target_include_directories(SpaceKernel 
PUBLIC
	.
)
# target dependencies
target_link_libraries(SpaceKernel 
PUBLIC 
	SpaceKernelLinux
)