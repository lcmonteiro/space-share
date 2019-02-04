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
)
# ---------------------------------------------------------
# add temporary
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestTemporary 
SOURCES 
    TestKernel/TestFrame.cpp
INCLUDES
    ../../Space/SKernel
    ../../Space/SHelper
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------