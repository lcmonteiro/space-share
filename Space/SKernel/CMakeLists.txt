cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# platform dependencies ${includes} and ${sources}
# -----------------------------------------------------------------------------
if(true)
	# linux folder for core objects
	add_subdirectory(SLinux)
endif()
# -----------------------------------------------------------------------------
# SpaceKernel target
# -----------------------------------------------------------------------------
# object library
add_library(SpaceKernel OBJECT 
	${SOURCES}
	SContainer.cpp
	SAddress.cpp
	SFrame.cpp
)
# dependencies
target_include_directories(SpaceKernel
PUBLIC  
	${CMAKE_CURRENT_LIST_DIR}
	#$<TARGET_PROPERTY:SpaceResource,INTERFACE_INCLUDE_DIRECTORIES>
	#$<TARGET_PROPERTY:SpaceHelper  ,INTERFACE_INCLUDE_DIRECTORIES>
	#$<TARGET_PROPERTY:${LINKS}     ,INTERFACE_INCLUDE_DIRECTORIES>
PRIVATE 
	${INCLUDES}
	#$<TARGET_PROPERTY:SpaceMonitor ,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------