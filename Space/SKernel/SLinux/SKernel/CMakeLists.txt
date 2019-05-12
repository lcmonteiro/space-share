cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceKernelLinux target
# ---------------------------------------------------------
add_library(SpaceKernelLinux OBJECT
	SMonitorHandler.cpp
)
# includes
target_include_directories(SpaceKernelLinux 
PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
PRIVATE
	$<TARGET_PROPERTY:SpaceKernel,INTERFACE_INCLUDE_DIRECTORIES>
)
# ---------------------------------------------------------
# end 
# ---------------------------------------------------------
