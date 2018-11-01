cmake_minimum_required (VERSION 3.10)
project (Test)
# Configure google-test as a downloadable library.
include(GoogleTest.cmake)
#
add_executable(
    TestSample
    #INTERFACE
    TestSample.cpp
)

# This will automatically handle all of the lib linkage and include dirs
target_link_libraries(
    TestSample
PRIVATE
    GTest::GTest GTest::Main
)
add_test(NAME TestSample COMMAND TestSample)

