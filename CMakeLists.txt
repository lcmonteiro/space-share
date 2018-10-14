cmake_minimum_required (VERSION 3.8)
# project name
project (SpaceShare)
# definitions
add_definitions(-D__LOG__)
# folder for Applications
add_subdirectory(Applications)
# folder for Share algorithms
add_subdirectory(Share)
# folder for common use
add_subdirectory(Space)
# target
add_library(SpaceShare 
INTERFACE
)
# dependencies
target_link_libraries(SpaceShare 
INTERFACE
	Share 
	Space
)