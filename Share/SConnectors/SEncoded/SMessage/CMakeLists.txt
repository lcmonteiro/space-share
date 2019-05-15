cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# -----------------------------------------------------------------------------
# ShareConnectorEncodedMessage interface
# -----------------------------------------------------------------------------
# interface library
add_library(ShareConnectorEncodedMessage INTERFACE)
# dependencies
target_include_directories(ShareConnectorEncodedMessage
INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
	$<TARGET_PROPERTY:ShareConnectorEncodedMessageKernel,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------