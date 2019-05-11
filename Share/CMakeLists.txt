cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# Share project
# ---------------------------------------------------------
#project (Share)
# folder for connectors
add_subdirectory(SConnectors)
# folder for functions
add_subdirectory(SFunctions)
# folder for interfaces
add_subdirectory(SInterfaces)
# folder for Modules
add_subdirectory(SModules)
# folder for kernel
add_subdirectory(SKernel)
# ---------------------------------------------------------
# ShareFunction target
# ---------------------------------------------------------
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
# ---------------------------------------------------------
# end
# ---------------------------------------------------------