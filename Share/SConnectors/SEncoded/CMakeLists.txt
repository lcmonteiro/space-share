cmake_minimum_required (VERSION 3.8)
# folder for Decoded
add_subdirectory(SMessage)
# folder for Encoded
add_subdirectory(SStream)
# ---------------------------------------------------------
# ShareConnectorEncoded target
# ---------------------------------------------------------
create_container(
TARGET	
	ShareConnectorEncoded 
PUBLIC_LINKS
	ShareConnectorEncodedMessage
	ShareConnectorEncodedStream
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------