cmake_minimum_required (VERSION 3.10)
# with JAVA_HOME 
find_package(JNI REQUIRED)
# ---------------------------------------------------------
# Bindings target
# ---------------------------------------------------------
add_library(BindingBufferShareJavaNative 
    BufferShareJNI.cpp
)
# includes
target_include_directories(BindingBufferShareJavaNative
    PUBLIC
    ${JNI_INCLUDE_DIRS}
)
# dependencies
target_link_libraries(BindingBufferShareJavaNative 
PRIVATE
    ShareInterface
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------