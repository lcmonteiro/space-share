cmake_minimum_required (VERSION 3.8)
# target
add_library(SpaceResourceLinux 
STATIC
	SLinuxDirectory.cpp
	SLinuxEvent.cpp
	SLinuxFile.cpp
	SLinuxIRC.cpp
	SLinuxPoll.cpp
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
	${CMAKE_CURRENT_LIST_DIR}/SRemoteResource.cpp
	PARENT_SCOPE
)