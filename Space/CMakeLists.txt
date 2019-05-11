cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# Space project
# ---------------------------------------------------------
#project (Space)
# folder for core objects
add_subdirectory(SKernel)
# folder for Monitor objects
add_subdirectory(SMonitors)
# folder for Resources
add_subdirectory(SResources)
# folder for Resources
add_subdirectory(SHelpers)
# ---------------------------------------------------------
# Space target
# ---------------------------------------------------------
add_library(Space INTERFACE)
# dependencies
target_link_libraries(Space 
INTERFACE 
	SpaceKernel 
	SpaceMonitor 
	SpaceResource
)
# includes
target_include_directories(Space 
INTERFACE
	.
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------