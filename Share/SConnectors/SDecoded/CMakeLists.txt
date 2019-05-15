cmake_minimum_required (VERSION 3.8)
# folder for message
add_subdirectory(SMessage)
# folder for stream
add_subdirectory(SStream)
# ---------------------------------------------------------
# ShareConnectorDecoded interface
# ---------------------------------------------------------
# interface library
add_library(ShareConnectorDecoded INTERFACE)
# dependencies
target_include_directories(ShareConnectorDecoded
INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
	$<TARGET_PROPERTY:ShareConnectorDecodedMessage,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:ShareConnectorDecodedStream,INTERFACE_INCLUDE_DIRECTORIES>
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------