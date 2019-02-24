cmake_minimum_required (VERSION 3.8)
# target
add_library(ShareKernelCodec 
STATIC
	SCodec.cpp
	SCodecStamp.cpp
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