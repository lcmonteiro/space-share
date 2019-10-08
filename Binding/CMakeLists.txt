cmake_minimum_required (VERSION 3.10)
# ---------------------------------------------------------
# subdirectories
# ---------------------------------------------------------
# folder for BufferShare
add_subdirectory(BufferShare)
# folder for NetShare
add_subdirectory(NetShare)
# ---------------------------------------------------------
# Bindings target
# ---------------------------------------------------------
add_library(Bindings INTERFACE)
# dependencies
target_link_libraries(Bindings 
INTERFACE
    BindingBufferShare
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------