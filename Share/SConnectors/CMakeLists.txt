cmake_minimum_required (VERSION 3.8)
# folder for Decoded
add_subdirectory(SDecoded)
# folder for Encoded
add_subdirectory(SEncoded)
# -----------------------------------------------------------------------------
# ShareConnector collector
# -----------------------------------------------------------------------------
# interface library
add_library(ShareConnector INTERFACE)
# dependencies
target_include_directories(ShareConnector
INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
	$<TARGET_PROPERTY:ShareConnectorDecoded,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:ShareConnectorEncoded,INTERFACE_INCLUDE_DIRECTORIES>
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------