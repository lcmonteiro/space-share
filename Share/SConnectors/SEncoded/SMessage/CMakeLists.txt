cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# ---------------------------------------------------------
# ShareConnectorEncodedMessage target
# ---------------------------------------------------------
create_container(
TARGET	
	ShareConnectorEncodedMessage	 
PUBLIC_LINKS
	ShareConnectorEncodedMessageKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------