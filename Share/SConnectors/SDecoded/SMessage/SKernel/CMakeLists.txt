cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareConnectorDecodedMessageKernel container
# ---------------------------------------------------------
create_container(
TARGET	
	ShareConnectorDecodedMessageKernel 
SOURCES
	SIDirConnector.cpp
	SODirConnector.cpp
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
	SpaceKernel
	ShareKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------