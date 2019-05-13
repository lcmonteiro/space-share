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
LINKS
    SpaceHelper
DEPENDS
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
LINKS
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
LINKS
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
LINKS
    ShareModule
    ShareInterface
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------