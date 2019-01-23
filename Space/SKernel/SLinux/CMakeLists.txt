cmake_minimum_required (VERSION 3.8)
# SpaceShare target
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
# linux 
# ---------------------------------------------------------
# include directories
set(includes 
	${CMAKE_CURRENT_LIST_DIR}
	PARENT_SCOPE
)
# source files
set(sources  
	${CMAKE_CURRENT_LIST_DIR}/SMonitor.cpp
	${CMAKE_CURRENT_LIST_DIR}/STask.cpp
	PARENT_SCOPE
)
# link libraries
set(links  
	PARENT_SCOPE
)