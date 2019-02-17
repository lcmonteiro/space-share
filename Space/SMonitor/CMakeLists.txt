cmake_minimum_required (VERSION 3.8)
# folders
#add_subdirectory(SLinux)
# target
add_library(SpaceMonitor 
INTERFACE
)
# includes
target_include_directories(SpaceMonitor 
INTERFACE
	.
)
# dependencies
target_link_libraries(SpaceMonitor 
INTERFACE 
	SpaceKernel
)