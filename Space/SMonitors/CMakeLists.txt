cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceMonitor interface
# ---------------------------------------------------------
create_interface(
TARGET	
	SpaceMonitor 
INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
LINKS
	SpaceKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------