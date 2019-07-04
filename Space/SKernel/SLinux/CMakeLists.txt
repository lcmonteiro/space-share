cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# linux - interface 
# ---------------------------------------------------------
# add dependencies 
add_subdirectory(SKernel)
# include directories
set(includes 
	${includes}
	PARENT_SCOPE
)
# source files
set(sources
	${sources}
	${CMAKE_CURRENT_LIST_DIR}/SMonitor.cpp
	${CMAKE_CURRENT_LIST_DIR}/STask.cpp
	${CMAKE_CURRENT_LIST_DIR}/SLog.cpp
	PARENT_SCOPE
)
# source files
set(links
	${links}
	pthread
	PARENT_SCOPE
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------