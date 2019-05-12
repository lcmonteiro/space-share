cmake_minimum_required (VERSION 3.10)
# ---------------------------------------------------------
# add test for connector
# ---------------------------------------------------------
add_gtests(
TARGET 
    TestLegacyShare
SOURCES
    TestShare/main.cpp
    TestShare/SInterface/STestBasic.cpp
CONTAINERS
    ShareInterface
)
# ---------------------------------------------------------
# end
# ---------------------------------------------------------
