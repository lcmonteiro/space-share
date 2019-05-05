cmake_minimum_required (VERSION 3.8)
# folder for message
add_subdirectory(SMessage)
# folder for stream
add_subdirectory(SStream)
# ---------------------------------------------------------
# ShareConnectorDecoded target
# ---------------------------------------------------------
add_library(ShareConnectorDecoded
INTERFACE
)
# dependencies
target_link_libraries(ShareConnectorDecoded
INTERFACE 
	ShareConnectorDecodedMessage
	ShareConnectorDecodedStream
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------