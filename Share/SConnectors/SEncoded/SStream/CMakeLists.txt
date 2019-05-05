cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# ---------------------------------------------------------
# ShareConnectorEncodedStream target
# ---------------------------------------------------------
add_library(ShareConnectorEncodedStream 
INTERFACE
)
# dependencies
target_link_libraries(ShareConnectorEncodedStream
INTERFACE 
	ShareConnectorEncodedStreamKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------