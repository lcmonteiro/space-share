cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareConnectorEncodedMessageKernel target
# ---------------------------------------------------------
create_container(
TARGET	
	ShareConnectorEncodedMessageKernel	 
SOURCES
	SIDirConnector.cpp
	SIIrcConnector.cpp
	SIOIrcConnector.cpp
	SODirConnector.cpp
	SOIrcConnector.cpp
PUBLIC_INCLUDES
	.
PUBLIC_LINKS
	SpaceResource
	ShareKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------