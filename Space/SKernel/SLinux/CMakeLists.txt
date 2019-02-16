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
	PARENT_SCOPE
)
# source files
set(sources  
	${CMAKE_CURRENT_LIST_DIR}/SMonitor.cpp
	${CMAKE_CURRENT_LIST_DIR}/STask.cpp
	${CMAKE_CURRENT_LIST_DIR}/SLog.cpp
	PARENT_SCOPE
)
# link libraries
set(links
	SpaceKernelLinux
	PARENT_SCOPE
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------