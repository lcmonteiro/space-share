cmake_minimum_required (VERSION 3.8)
# SpaceShare target
add_library(SpaceKernelLinux 
STATIC
	SLinuxTask.cpp
)
# includes
target_include_directories(SpaceKernelLinux 
PUBLIC
	.
)
#dependencies
target_link_libraries(SpaceKernelLinux
PRIVATE 
	pthread
	SpaceKernel
	SpaceMonitorLinux
PUBLIC
	SpaceResourceLinux
)