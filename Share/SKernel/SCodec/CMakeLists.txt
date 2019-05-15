cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareKernelCodec target
# ---------------------------------------------------------
# object library
add_library(ShareKernelCodec OBJECT 
	SEngineCodec.cpp
	SStampCodec.cpp
)
# dependencies
target_include_directories(ShareKernelCodec
PUBLIC  
	${CMAKE_CURRENT_LIST_DIR}
	#$<TARGET_PROPERTY:SpaceKernel,INTERFACE_INCLUDE_DIRECTORIES>
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------