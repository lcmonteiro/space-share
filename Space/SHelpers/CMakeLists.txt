cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# SpaceHelper container
# ---------------------------------------------------------
create_container(
TARGET	
	SpaceHelper 
SOURCES
	SBase64.cpp
	SHash.cpp
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
	SpaceKernel
	SpaceResource
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------