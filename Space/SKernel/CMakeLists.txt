cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# platform dependencies ${includes} and ${sources}
# ---------------------------------------------------------
if(true)
	# linux folder for core objects
	add_subdirectory(SLinux)
endif()
# ---------------------------------------------------------
# SpaceKernel package
# ---------------------------------------------------------
create_package(
TARGET	
	SpaceKernel 
SOURCES
	${sources}
	SContainer.cpp
	SAddress.cpp
	SFrame.cpp
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PRIVATE_INCLUDES
	${includes}
PUBLIC_LINKS
	${links}
	SpaceResource
	SpaceMonitor
	SpaceHelper
PRIVATE_LINKS
	SpaceMonitor
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------