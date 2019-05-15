cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# -----------------------------------------------------------------------------
# ShareConnectorDecodedStream target
# -----------------------------------------------------------------------------
# interface library
add_library(ShareConnectorDecodedStream INTERFACE)
# dependencies
target_include_directories(ShareConnectorDecodedMessage
INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
	$<TARGET_PROPERTY:ShareConnectorDecodedStreamKernel,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------