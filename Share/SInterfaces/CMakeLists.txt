cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareInterface target
# ---------------------------------------------------------
add_library(ShareInterface 
	SBufferShare.cpp
	SMachine.cpp
)
# includes
target_include_directories(ShareInterface 
PUBLIC
	.
)
#dependencies
target_link_libraries(ShareInterface
PUBLIC
	ShareModule
	ShareKernel
	SpaceMonitor
	SpaceResource
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------