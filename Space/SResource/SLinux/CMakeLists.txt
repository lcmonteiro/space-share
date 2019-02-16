cmake_minimum_required (VERSION 3.8)
# include directories
set(includes 
	${CMAKE_CURRENT_LIST_DIR}
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
	SpaceMonitorLinux
	PARENT_SCOPE
)