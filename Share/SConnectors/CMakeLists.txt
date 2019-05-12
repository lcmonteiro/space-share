cmake_minimum_required (VERSION 3.8)
# folder for Decoded
add_subdirectory(SDecoded)
# folder for Encoded
add_subdirectory(SEncoded)
# ---------------------------------------------------------
# ShareConnector target
# ---------------------------------------------------------
create_container(
TARGET	
	ShareConnector 
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
	ShareConnectorDecoded
	ShareConnectorEncoded
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------