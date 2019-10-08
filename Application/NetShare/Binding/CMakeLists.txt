cmake_minimum_required (VERSION 3.10)
# ---------------------------------------------------------
# subdirectories
# ---------------------------------------------------------
# folder for Java Binding
add_subdirectory(Java)
# ---------------------------------------------------------
# Bindings target
# ---------------------------------------------------------
add_library(BindingNetShare INTERFACE)
# dependencies
target_link_libraries(BindingNetShare 
INTERFACE
	BindingNetShareJava
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------