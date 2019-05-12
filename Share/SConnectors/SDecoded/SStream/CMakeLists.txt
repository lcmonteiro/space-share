cmake_minimum_required (VERSION 3.8)
# folder for Kernel
add_subdirectory(SKernel)
# ---------------------------------------------------------
# ShareConnectorDecodedStream target
# ---------------------------------------------------------
create_interface(
TARGET	
	ShareConnectorDecodedStream	 
LINKS
	ShareConnectorDecodedStreamKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------