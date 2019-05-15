cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# SpaceHelper package
# -----------------------------------------------------------------------------
# object library
add_library(SpaceHelper OBJECT
	SBase64.cpp
	SHash.cpp
)
# dependencies
target_include_directories(SpaceHelper
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}
	#$<TARGET_PROPERTY:ShareKernel,  INTERFACE_INCLUDE_DIRECTORIES>
	#$<TARGET_PROPERTY:SpaceResource,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------