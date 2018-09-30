cmake_minimum_required (VERSION 3.8)
# folder for core objects
add_subdirectory(SLinux)
# SpaceShare target
add_library(SpaceResource
INTERFACE
)
# includes
target_include_directories(SpaceResource 
INTERFACE
	.
)
# target dependencies
target_link_libraries(SpaceResource 
INTERFACE 
	SpaceMonitor
	SpaceResourceLinux
)