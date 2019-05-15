cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# platform dependencies ${includes} and ${sources}
# -----------------------------------------------------------------------------
if(true)
	# linux folder for core objects
	add_subdirectory(SLinux)
endif()
# -----------------------------------------------------------------------------
# SpaceResource container
# -----------------------------------------------------------------------------
# object library
add_library(SpaceResource OBJECT
	${SOURCES}
	SIRCResource.cpp
)
# dependencies
target_include_directories(SpaceResource
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}
	#$<TARGET_PROPERTY:ShareKernel, INTERFACE_INCLUDE_DIRECTORIES>
PRIVATE
	${INCLUDES}
	#$<TARGET_PROPERTY:SpaceMonitor,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# End
# -----------------------------------------------------------------------------