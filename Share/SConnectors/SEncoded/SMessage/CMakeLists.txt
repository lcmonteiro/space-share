cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# ---------------------------------------------------------
# ShareConnectorEncodedMessage target
# ---------------------------------------------------------
add_library(ShareConnectorEncodedMessage
INTERFACE
)
# dependencies
target_link_libraries(ShareConnectorEncodedMessage
INTERFACE 
	ShareConnectorEncodedMessageKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------