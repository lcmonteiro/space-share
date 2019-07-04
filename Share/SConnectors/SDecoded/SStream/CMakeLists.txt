cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# ---------------------------------------------------------
# ShareConnectorDecodedStream target
# ---------------------------------------------------------
add_library(ShareConnectorDecodedStream INTERFACE)
# dependencies
target_link_libraries(ShareConnectorDecodedStream
INTERFACE 
	SpaceKernel
	ShareConnectorDecodedStreamKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------