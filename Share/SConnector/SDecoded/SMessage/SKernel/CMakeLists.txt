cmake_minimum_required (VERSION 3.8)
# target
add_library(ShareConnectorDecodedMessageKernel 
STATIC
	SIDirConnector.cpp
	SODirConnector.cpp
	SOFileConnector.cpp
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