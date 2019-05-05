cmake_minimum_required (VERSION 3.8)
# folder for Decoded
add_subdirectory(SDecoded)
# folder for Encoded
add_subdirectory(SEncoded)
# ---------------------------------------------------------
# ShareConnector target
# ---------------------------------------------------------
add_library(ShareConnector 
INTERFACE
)
# includes
target_include_directories(ShareConnector 
INTERFACE
	.
)
# dependencies
target_link_libraries(ShareConnector
INTERFACE 
	ShareConnectorDecoded
	ShareConnectorEncoded
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------