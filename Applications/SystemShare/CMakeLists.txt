cmake_minimum_required (VERSION 3.8)
# project
project (SystemShare)
# -----------------------------------------------------------------------------
# SystemShare target
# -----------------------------------------------------------------------------
# executable
add_executable(SystemShare
	Source/main.cpp
)
# dependencies
target_sources(SystemShare
PRIVATE 
	$<TARGET_OBJECTS:ShareInterface>
)
target_link_libraries(SystemShare
PRIVATE 
	pthread
)
# -----------------------------------------------------------------------------
# end
# -----------------------------------------------------------------------------