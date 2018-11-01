cmake_minimum_required (VERSION 3.10)
project (Test)
# folder for core objects
#include(GoogleTest)
# 
#file(GLOB testsuits "*.cpp")
#
#add_executable(TestSample ${testsuits})
# sample
#target_link_libraries(TestSample google
#gtest_add_tests(TARGET	TestSample)

# Configure google-test as a downloadable library.
include(GoogleTest.cmake)

include(CTest)

enable_testing()

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

# Tell ctest about my tests
# include(GoogleTest)
# gtest_add_tests(
#     TARGET      TestSample
#     #TEST_LIST   myTests_targets
# )

# set each target to timeout if not finished within 10 sec
#set_tests_properties(${myTests_targets} PROPERTIES TIMEOUT 10)

#find_package(GTest REQUIRED)
#include(GoogleTest)
 
#find_package(GTest)
#add_executable(tests TestSample.cpp)
#target_link_libraries(tests GTest::GTest)
 
#gtest_add_tests(TARGET tests TEST_PREFIX old:)
#gtest_discover_tests(TestSample TEST_PREFIX new:)
add_test(NAME TestSample COMMAND TestSample)

