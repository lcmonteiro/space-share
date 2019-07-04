cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# linux - kernel 
# ---------------------------------------------------------
add_subdirectory(SKernel)
# ---------------------------------------------------------
# linux - interface 
# ---------------------------------------------------------
# include directories
set(includes 
	${CMAKE_CURRENT_LIST_DIR}
	${includes}
	PARENT_SCOPE
)
# source files
set(sources  
	${CMAKE_CURRENT_LIST_DIR}/SDirectoryResource.cpp
	${CMAKE_CURRENT_LIST_DIR}/SRemoteResource.cpp
	${CMAKE_CURRENT_LIST_DIR}/SLocalResource.cpp
	${CMAKE_CURRENT_LIST_DIR}/SEventResource.cpp
	${CMAKE_CURRENT_LIST_DIR}/SFileResource.cpp
	PARENT_SCOPE
)
# link libraries
set(links
	SpaceResourceLinux
	PARENT_SCOPE
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------