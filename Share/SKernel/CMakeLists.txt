cmake_minimum_required (VERSION 3.8)
# folder for core objects
add_subdirectory(SCodec)
# -----------------------------------------------------------------------------
# ShareKernel target
# -----------------------------------------------------------------------------
# object library
add_library(ShareKernel OBJECT 
	SConnector.cpp
	SDocument.cpp
	SModule.cpp
)
# dependencies
target_include_directories(ShareKernel
PUBLIC  
	${CMAKE_CURRENT_LIST_DIR}
	#$<TARGET_PROPERTY:ShareKernelCodec,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------