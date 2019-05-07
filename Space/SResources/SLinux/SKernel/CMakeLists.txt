cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceResourceLinux target
# ---------------------------------------------------------
add_library(SpaceResourceLinux INTERFACE
)
# includes
target_include_directories(SpaceKernelLinux 
INTERFACE
	.
)
#dependencies
target_link_libraries(SpaceResourceLinux
)
# ---------------------------------------------------------
# end 
# ---------------------------------------------------------
