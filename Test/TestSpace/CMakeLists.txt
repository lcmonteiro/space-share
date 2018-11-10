cmake_minimum_required (VERSION 3.10)
#
# add
# 
add_gtests(
TARGET 
    TestKernel 
SOURCES 
    TestKernel/TestVariable.cpp
    TestKernel/TestCommand.cpp
    TestKernel/TestProcess.cpp
TARGETS
    SpaceKernel
)