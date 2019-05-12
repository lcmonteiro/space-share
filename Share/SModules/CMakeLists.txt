cmake_minimum_required (VERSION 3.8)
# ---------------------------------------------------------
# ShareModule target
# ---------------------------------------------------------
create_container(
TARGET	
	ShareModule 
PUBLIC_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}
PUBLIC_LINKS
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