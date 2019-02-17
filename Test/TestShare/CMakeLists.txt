cmake_minimum_required (VERSION 3.10)
# ---------------------------------------------------------
# add test for connector
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestShareConnector
SOURCES
    TestConnector/TestDecodedMessageUDP.cpp
DEPENDS
    ShareConnector
    SpaceHelper
)
# ---------------------------------------------------------
# add test for share kernel 
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestShareKernel
SOURCES
    TestKernel/TestCodec.cpp
DEPENDS
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
DEPENDS
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
DEPENDS
    ShareModule
    ShareInterface
)