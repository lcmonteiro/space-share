cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# platform dependencies ${includes} and ${sources}
# ---------------------------------------------------------
if(true)
	# linux folder for core objects
	add_subdirectory(SLinux)
endif()
# ---------------------------------------------------------
# SpaceKernel target
# ---------------------------------------------------------
add_library(SpaceKernel 
STATIC
    ${sources}
	SContainer.cpp
	SAddress.cpp
	SFrame.cpp
	SLog.cpp
)
# includes
target_include_directories(SpaceKernel 
PUBLIC
	${CMAKE_CURRENT_LIST_DIR}	
PRIVATE
	${includes}
)
# target dependencies
target_link_libraries(SpaceKernel 
PUBLIC 
	SpaceKernelLinux
)