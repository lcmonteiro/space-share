cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# ShareConnectorEncodedMessageKernel package
# -----------------------------------------------------------------------------
# object library
add_library(ShareConnectorEncodedMessageKernel OBJECT
	SIDirConnector.cpp
	SIIrcConnector.cpp
	SIOIrcConnector.cpp
	SODirConnector.cpp
	SOIrcConnector.cpp
)
# dependencies
target_include_directories(ShareConnectorEncodedMessageKernel
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}
	#$<TARGET_PROPERTY:SpaceResource,INTERFACE_INCLUDE_DIRECTORIES>
	#$<TARGET_PROPERTY:ShareKernel,  INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------