cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# platform dependencies ${includes} and ${sources}
# ---------------------------------------------------------
if(true)
	# linux folder for core objects
	add_subdirectory(SLinux)
endif()
# ---------------------------------------------------------
# SpaceResource target
# ---------------------------------------------------------
add_library(SpaceResource
	${sources}
	SIRCResource.cpp
)
# includes
target_include_directories(SpaceResource 
PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
PRIVATE
	${includes}
)
# dependencies
target_link_libraries(SpaceResource 
PUBLIC
	SpaceKernel
PRIVATE
	SpaceMonitor
	SpaceHelper
)