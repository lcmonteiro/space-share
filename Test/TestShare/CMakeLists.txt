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
    TestModule/TestSpread.cpp
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
    TestInterface/TestBufferShare.cpp
DEPENDS
    ShareModule
    ShareInterface
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------