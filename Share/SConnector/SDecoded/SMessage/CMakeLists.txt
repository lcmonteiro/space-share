cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# folder for Kernel
add_subdirectory(STools)
# target
add_library(ShareConnectorDecodedMessage
INTERFACE
)
# includes
target_include_directories(ShareConnectorDecodedMessage 
INTERFACE
	.
)
# dependencies
target_link_libraries(ShareConnectorDecodedMessage
INTERFACE 
	ShareConnectorDecodedMessageKernel
	ShareConnectorDecodedMessageTools
	SpaceKernel
)