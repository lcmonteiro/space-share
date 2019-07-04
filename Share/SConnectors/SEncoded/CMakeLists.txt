cmake_minimum_required (VERSION 3.8)
# folder for Decoded
add_subdirectory(SMessage)
# folder for Encoded
add_subdirectory(SStream)
# ---------------------------------------------------------
# ShareConnectorEncoded target
# ---------------------------------------------------------
add_library(ShareConnectorEncoded INTERFACE)
# dependencies
target_link_libraries(ShareConnectorEncoded
INTERFACE 
	ShareConnectorEncodedMessage
	ShareConnectorEncodedStream
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------