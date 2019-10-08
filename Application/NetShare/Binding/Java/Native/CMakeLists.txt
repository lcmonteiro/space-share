cmake_minimum_required (VERSION 3.10)
# with JAVA_HOME 
find_package(JNI REQUIRED)
# ---------------------------------------------------------
# Bindings target
# ---------------------------------------------------------
add_library(BindingNetShareJavaNative 
    NetShareJNI.cpp
)
# includes
target_include_directories(BindingNetShareJavaNative
    PUBLIC
    ${JNI_INCLUDE_DIRS}
)
# dependencies
target_link_libraries(BindingNetShareJavaNative 
PRIVATE
    ShareInterface
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------