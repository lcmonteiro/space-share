cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceMonitorLinux target 
# ---------------------------------------------------------
add_library(SpaceMonitorLinux INTERFACE
)
# includes
target_include_directories(SpaceMonitorLinux 
INTERFACE
	.
)
#dependencies
target_link_libraries(SpaceMonitorLinux
INTERFACE 
	SpaceKernel
	SpaceMonitor
	SpaceKernelLinux
	SpaceResourceLinux
)
