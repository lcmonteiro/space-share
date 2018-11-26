cmake_minimum_required (VERSION 3.10)
#
# add
# 
add_gtests(
TARGET 
    TestSpaceKernel 
SOURCES 
    TestKernel/TestVariable.cpp
    TestKernel/TestCommand.cpp
    TestKernel/TestProcess.cpp
DEPENDS
    SpaceKernel
)