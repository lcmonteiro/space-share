cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# platform dependencies ${includes} and ${sources}
# ---------------------------------------------------------
if(true)
	# linux folder for core objects
	add_subdirectory(SLinux)
endif()
# ---------------------------------------------------------
# SpaceResource container
# ---------------------------------------------------------
create_container(
TARGET	
	SpaceResource 
SOURCES
	${sources}
	SIRCResource.cpp
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
	SpaceKernel
PRIVATE_INCLUDES
	${includes}
PRIVATE_LINKS
	SpaceMonitor
)
# ---------------------------------------------------------
# End
# ---------------------------------------------------------