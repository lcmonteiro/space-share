cmake_minimum_required (VERSION 3.10)
# ---------------------------------------------------------
# BufferShareJava project
# ---------------------------------------------------------
project (BindingBufferShareJava)
# definitions
add_definitions(-D__LOG__)
# ---------------------------------------------------------
# subdirectories
# ---------------------------------------------------------
# folder for Java Binding
add_subdirectory(Native)
# ---------------------------------------------------------
# Bindings target
# ---------------------------------------------------------
add_library(BindingBufferShareJava INTERFACE)
# dependencies
target_link_libraries(BindingBufferShareJava 
INTERFACE
	BindingBufferShareJavaNative
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------