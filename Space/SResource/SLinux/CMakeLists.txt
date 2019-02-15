cmake_minimum_required (VERSION 3.8)
# target
add_library(SpaceResourceLinux 
STATIC
	SLinuxResource.cpp
	SLinuxSocket.cpp
)
# includes
target_include_directories(SpaceResourceLinux 
PUBLIC
	.
)
#dependencies
target_link_libraries(SpaceResourceLinux
PRIVATE
PUBLIC
	SpaceMonitorLinux
	SpaceHelper
)

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