cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceKernelLinux target
# ---------------------------------------------------------
add_library(SpaceKernelLinux STATIC
	SMonitorHandler.cpp
)
# includes
target_include_directories(SpaceKernelLinux 
PUBLIC
	.
)
#dependencies
target_link_libraries(SpaceKernelLinux
PUBLIC 
	pthread
	SpaceKernel
	SpaceMonitorLinux
	SpaceResourceLinux
)
# ---------------------------------------------------------
# end 
# ---------------------------------------------------------
