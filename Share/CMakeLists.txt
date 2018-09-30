cmake_minimum_required (VERSION 3.8)
# project
project (Share)
# folder for connectors
add_subdirectory(SConnector)
# folder for functions
add_subdirectory(SFunction)
# folder for interfaces
add_subdirectory(SInterface)
# folder for kernel
add_subdirectory(SKernel)
# target
add_library(Share INTERFACE)
# dependencies
target_link_libraries(Share 
INTERFACE 
	ShareConnector 
	ShareFunction 
	ShareInterface 
	ShareKernel
)
# includes
target_include_directories(Share 
INTERFACE
	.
)