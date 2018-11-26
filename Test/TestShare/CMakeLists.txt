cmake_minimum_required (VERSION 3.10)
#
# add test for share kernel 
# 
add_gtests(
TARGET 
    TestShareKernel
SOURCES
    TestKernel/TestModule.cpp
DEPENDS
    ShareModule
)
#
# add test for interface
#
add_gtests(
TARGET 
    TestShareInterface
SOURCES
    TestInterface/TestMachine.cpp
DEPENDS
    ShareModule
    ShareInterface
)
