cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareConnectorEncodedMessageKernel target
# ---------------------------------------------------------
add_library(ShareConnectorEncodedMessageKernel 
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
# ---------------------------------------------------------
# end
# ---------------------------------------------------------