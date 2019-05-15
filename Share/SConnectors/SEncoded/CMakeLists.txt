cmake_minimum_required (VERSION 3.8)
# folder for Decoded
add_subdirectory(SMessage)
# folder for Encoded
add_subdirectory(SStream)
# ---------------------------------------------------------
# ShareConnectorEncoded interface
# ---------------------------------------------------------
# interface library
add_library(ShareConnectorEncoded INTERFACE)
# dependencies
target_include_directories(ShareConnectorEncoded
INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
	$<TARGET_PROPERTY:ShareConnectorEncodedMessage,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:ShareConnectorEncodedStream,INTERFACE_INCLUDE_DIRECTORIES>
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------