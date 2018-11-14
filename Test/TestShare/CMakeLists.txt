cmake_minimum_required (VERSION 3.10)
#
# add
# 
add_gtests(
TARGET 
    TestShareKernel
SOURCES
    TestKernel/TestModule.cpp
TARGETS
    ShareKernelModule
)
