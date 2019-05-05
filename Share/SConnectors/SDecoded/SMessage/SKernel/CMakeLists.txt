cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareConnectorDecodedMessageKernel target
# ---------------------------------------------------------
add_library(ShareConnectorDecodedMessageKernel 
STATIC
	SIDirConnector.cpp
	SODirConnector.cpp
)
# includes
target_include_directories(ShareConnectorDecodedMessageKernel 
PUBLIC
	.
)
# dependencies
target_link_libraries(ShareConnectorDecodedMessageKernel
PUBLIC 
	SpaceResource
	SpaceKernel
	ShareKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------