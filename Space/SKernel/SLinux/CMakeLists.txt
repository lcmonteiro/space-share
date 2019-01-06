cmake_minimum_required (VERSION 3.8)
# SpaceShare target
add_library(SpaceKernelLinux INTERFACE
)
# includes
target_include_directories(SpaceKernelLinux 
INTERFACE
	.
)
#dependencies
target_link_libraries(SpaceKernelLinux
INTERFACE 
	pthread
	SpaceKernel
	SpaceMonitorLinux
	SpaceResourceLinux
)
# ---------------------------------------------------------
# linux 
# ---------------------------------------------------------
# include directories
set(includes 
	${CMAKE_CURRENT_LIST_DIR}
	PARENT_SCOPE
)
# source files
set(sources  
	${CMAKE_CURRENT_LIST_DIR}/STask.cpp
	PARENT_SCOPE
)
# link libraries
set(links  
	PARENT_SCOPE
)