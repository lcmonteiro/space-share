cmake_minimum_required (VERSION 3.10)
# ---------------------------------------------------------
# add kernel test 
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestSpaceKernel 
SOURCES 
    TestKernel/TestVariable.cpp
    TestKernel/TestCommand.cpp
    TestKernel/TestProcess.cpp
    TestKernel/TestAddress.cpp
    TestKernel/TestContainer.cpp
DEPENDS
    SpaceKernel
)
# ---------------------------------------------------------
# add kelnel test 
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestSpaceResource 
SOURCES 
    TestResource/TestFileResource.cpp
DEPENDS
    SpaceResource
    SpaceKernel
)