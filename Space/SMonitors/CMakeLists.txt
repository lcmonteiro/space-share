cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceMonitor target
# ---------------------------------------------------------
create_container(
TARGET	
	SpaceMonitor 
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
	SpaceKernel
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------