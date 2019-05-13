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
    TestKernel/TestFrame.cpp
    TestKernel/TestBuffer.cpp
LINKS
    SpaceKernel
    SpaceHelper
)
# ---------------------------------------------------------
# add resource test 
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestSpaceResource 
SOURCES 
    TestResource/TestFileResource.cpp
    TestResource/TestLocalResource.cpp
    TestResource/TestRemoteResource.cpp
LINKS
    SpaceResource
    SpaceKernel
    SpaceHelper
)
# ---------------------------------------------------------
# add monitor test 
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestSpaceMonitor 
SOURCES 
    TestMonitor/TestResourceMonitor.cpp
    TestMonitor/TestRoadMonitor.cpp
LINKS
    SpaceResource
    SpaceKernel
    SpaceHelper
DEPENDS
    SpaceMonitor
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------