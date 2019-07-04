cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareKernelCodec target
# ---------------------------------------------------------
add_library(ShareKernelCodec
	SEngineCodec.cpp
	SStampCodec.cpp
)
# includes
target_include_directories(ShareKernelCodec 
PUBLIC
	.
)
# target dependencies
target_link_libraries(ShareKernelCodec 
PRIVATE 
	SpaceKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------