cmake_minimum_required (VERSION 3.8)
# folder for Decoded
add_subdirectory(SDecoded)
# folder for Encoded
add_subdirectory(SEncoded)
# ---------------------------------------------------------
# ShareConnector collector
# ---------------------------------------------------------
create_interface(
TARGET	
	ShareConnector 
INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
LINKS
	ShareConnectorDecoded
	ShareConnectorEncoded
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------