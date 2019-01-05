cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceMonitorLinux target 
# ---------------------------------------------------------
add_library(SpaceMonitorLinux 
STATIC
	SMonitorHandler.cpp
)
# includes
target_include_directories(SpaceMonitorLinux 
PUBLIC
	.
)
#dependencies
target_link_libraries(SpaceMonitorLinux
PUBLIC 
	SpaceKernel
PRIVATE
	SpaceMonitor
	SpaceKernelLinux
	SpaceResourceLinux
)
