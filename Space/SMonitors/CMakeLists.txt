cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# SpaceMonitor interface
# -----------------------------------------------------------------------------
# interface library
add_library(SpaceMonitor INTERFACE)
# dependencies
target_include_directories(SpaceMonitor
INTERFACE
	$<TARGET_PROPERTY:ShareKernel,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------