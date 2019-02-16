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
DEPENDS
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
    TestResource/TestRemoteResource.cpp
DEPENDS
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
DEPENDS
    SpaceResource
    SpaceMonitor
    SpaceKernel
    SpaceHelper
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------