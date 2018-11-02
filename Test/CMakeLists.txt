cmake_minimum_required (VERSION 3.10)
project (Test)
# Configure google-test as a downloadable library.
include(GoogleTest.cmake)
#
function(add_gtests target sources)
    add_executable (
        ${target} ${sources}
    )
    target_link_libraries(
        ${target}
    PRIVATE
       GTest::GTest GTest::Main
    )
    add_test(NAME ${target} COMMAND ${target})
endfunction()
#
# add Test sample
add_gtests(TestSample TestSample.cpp)

