cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareFunction target
# ---------------------------------------------------------
add_library(ShareFunction INTERFACE)
# includes
target_include_directories(ShareFunction 
INTERFACE
	.
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------