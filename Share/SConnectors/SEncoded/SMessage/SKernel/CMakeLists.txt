cmake_minimum_required (VERSION 3.8)
# target
add_library(ShareConnectorEncodedMessageKernel 
STATIC
	SIDirConnector.cpp
	SIIrcConnector.cpp
	SIOIrcConnector.cpp
	SODirConnector.cpp
	SOIrcConnector.cpp
)
# includes
target_include_directories(ShareConnectorEncodedMessageKernel 
PUBLIC
	.
)
# dependencies
target_link_libraries(ShareConnectorEncodedMessageKernel
PUBLIC
	SpaceResource
	ShareKernel
)