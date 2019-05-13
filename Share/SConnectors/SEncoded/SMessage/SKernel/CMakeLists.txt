cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareConnectorEncodedMessageKernel package
# ---------------------------------------------------------
create_package(
TARGET	
	ShareConnectorEncodedMessageKernel	 
SOURCES
	SIDirConnector.cpp
	SIIrcConnector.cpp
	SIOIrcConnector.cpp
	SODirConnector.cpp
	SOIrcConnector.cpp
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
	SpaceResource
	ShareKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------