cmake_minimum_required (VERSION 3.8)
# folder for core objects
add_subdirectory(SCodec)
# ---------------------------------------------------------
# ShareKernel target
# ---------------------------------------------------------
add_library(ShareKernel
	SConnector.cpp
	SDocument.cpp
	SModule.cpp
)
# includes
target_include_directories(ShareKernel 
PUBLIC
	.
)
# target dependencies
target_link_libraries(ShareKernel 
PUBLIC
	SpaceKernel
	ShareKernelCodec
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------