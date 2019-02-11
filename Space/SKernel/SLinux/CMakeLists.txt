cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# linux - private implement 
# ---------------------------------------------------------
add_subdirectory(SImplement)
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
	PARENT_SCOPE
)
# link libraries
set(links  
	PARENT_SCOPE
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------