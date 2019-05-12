cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# folder for Kernel
add_subdirectory(STools)
# ---------------------------------------------------------
# ShareConnectorDecodedMessage target
# ---------------------------------------------------------
create_interface(
TARGET	
	ShareConnectorDecodedMessage
PUBLIC_INCLUDES
	.
PUBLIC_LINKS
	ShareConnectorDecodedMessageKernel
	ShareConnectorDecodedMessageTools
	SpaceKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------