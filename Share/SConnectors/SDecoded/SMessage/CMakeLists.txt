cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# folder for Kernel
add_subdirectory(STools)
# -----------------------------------------------------------------------------
# ShareConnectorDecodedMessage target
# -----------------------------------------------------------------------------
# interface library
add_library(ShareConnectorDecodedMessage INTERFACE)
# dependencies
target_include_directories(ShareConnectorDecodedMessage
INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
	$<TARGET_PROPERTY:ShareConnectorDecodedMessageKernel,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:ShareConnectorDecodedMessageTools, INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------