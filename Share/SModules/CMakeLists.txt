cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareModule target
# ---------------------------------------------------------
create_interface(
TARGET	
	ShareModule 
INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
LINKS
	ShareConnector
	ShareFunction
	ShareKernel
	SpaceResource
	SpaceMonitor
	SpaceHelper
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------