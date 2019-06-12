cmake_minimum_required (VERSION 3.10)
enable_testing()
# ---------------------------------------------------------
# SpaceShare project
# ---------------------------------------------------------
project (SpaceShare)
# properties
set(CMAKE_CXX_STANDARD 14)
# definitions
add_definitions(-D__LOG__)
# ---------------------------------------------------------
# subdirectories
# ---------------------------------------------------------
# folder for applications
add_subdirectory(Applications)
# folder for binding
add_subdirectory(Bindings)
# folder for Share algorithms
add_subdirectory(Share)
# folder for common use
add_subdirectory(Space)
# folder for common use
add_subdirectory(Test)
# ---------------------------------------------------------
# SpaceShare target
# ---------------------------------------------------------
add_library(SpaceShare 
INTERFACE
)
# dependencies
target_link_libraries(SpaceShare 
INTERFACE
	Share 
	Space
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------