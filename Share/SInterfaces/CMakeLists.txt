cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareInterface target
# ---------------------------------------------------------
create_collector(
TARGET	
	ShareInterface 
SOURCES
	SBufferShare.cpp
	SMachine.cpp
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
	ShareModule
	ShareKernel
	SpaceMonitor
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------