cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# ShareModule target
# -----------------------------------------------------------------------------
# interface library
add_library(ShareModule INTERFACE)
# dependencies
target_include_directories(ShareModule
INTERFACE
	$<TARGET_PROPERTY:ShareConnector,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:ShareFunction, INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:ShareKernel,   INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:SpaceResource, INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:SpaceMonitor,  INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:SpaceHelper,   INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------