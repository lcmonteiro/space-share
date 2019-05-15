cmake_minimum_required (VERSION 3.8)
# -----------------------------------------------------------------------------
# ShareConnectorDecodedMessageKernel package
# -----------------------------------------------------------------------------
# object library
add_library(ShareConnectorDecodedMessageKernel OBJECT
	SIDirConnector.cpp
	SODirConnector.cpp
)
# dependencies
target_include_directories(ShareConnectorDecodedMessageKernel
PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}
PRIVATE
	#$<TARGET_PROPERTY:SpaceKernel, INTERFACE_INCLUDE_DIRECTORIES>
	#$<TARGET_PROPERTY:ShareKernel, INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------