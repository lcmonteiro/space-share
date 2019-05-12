cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareKernelCodec target
# ---------------------------------------------------------
add_library(ShareKernelCodec 
	SEngineCodec.cpp
	SStampCodec.cpp
	$<TARGET_OBJECTS:SpaceKernel>
)
# includes
target_include_directories(ShareKernelCodec 
PUBLIC
	.
	$<TARGET_PROPERTY:SpaceKernel,INTERFACE_INCLUDE_DIRECTORIES>
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------