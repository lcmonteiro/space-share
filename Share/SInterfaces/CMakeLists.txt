cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# ShareInterface target
# -----------------------------------------------------------------------------
# object library
add_library(ShareInterface OBJECT
	SBufferShare.cpp
	SMachine.cpp
)
# dependencies
target_include_directories(ShareInterface
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}
	#$<TARGET_PROPERTY:ShareModule, INTERFACE_INCLUDE_DIRECTORIES>
	#$<TARGET_PROPERTY:ShareKernel, INTERFACE_INCLUDE_DIRECTORIES>
	#$<TARGET_PROPERTY:SpaceMonitor,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------