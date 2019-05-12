cmake_minimum_required (VERSION 3.8)
# folder for message
add_subdirectory(SMessage)
# folder for stream
add_subdirectory(SStream)
# ---------------------------------------------------------
# ShareConnectorDecoded target
# ---------------------------------------------------------
create_container(
TARGET	
	ShareConnectorDecoded
PUBLIC_LINKS
	ShareConnectorDecodedMessage
	ShareConnectorDecodedStream
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------