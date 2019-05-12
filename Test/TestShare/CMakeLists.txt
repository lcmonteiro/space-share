cmake_minimum_required (VERSION 3.10)
# ---------------------------------------------------------
# add test for connector
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestShareConnector
SOURCES
    TestConnector/TestDecodedMessageUDP.cpp
    TestConnector/TestDecodedMessageFile.cpp
CONTAINERS
    SpaceHelper
    ShareConnector
)
# ---------------------------------------------------------
# add test for share kernel 
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestShareKernel
SOURCES
    TestKernel/TestCodec.cpp
CONTAINERS
    ShareModule
)
# ---------------------------------------------------------
# add test for module
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestShareModule
SOURCES
    TestModule/TestSpliter.cpp
    TestModule/TestSpread.cpp
CONTAINERS
    ShareModule
)
# ---------------------------------------------------------
# add test for interface
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestShareInterface
SOURCES
    TestInterface/TestMachine.cpp
    TestInterface/TestBufferShare.cpp
CONTAINERS
    ShareModule
    ShareInterface
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------