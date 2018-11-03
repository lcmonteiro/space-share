cmake_minimum_required (VERSION 3.10)
project (Test)
# Configure google-test as a downloadable library.
include(GoogleTest.cmake)
#
function(add_gtests)
    set(options)
    set(oneValue   TARGET)
    set(multiValue SOURCES TARGETS)
    cmake_parse_arguments(ARG "${options}" "${oneValue}" "${multiValue}" ${ARGN} )
    add_executable (
        ${ARG_TARGET} ${ARG_SOURCES}
    )
    target_link_libraries(
        ${ARG_TARGET}
    PRIVATE
       GTest::GTest GTest::Main ${ARG_TARGETS}
    )
    add_test(NAME ${ARG_TARGET} COMMAND ${ARG_TARGET})
endfunction()
#
# add Test sample
add_gtests(TARGET TestSample SOURCES TestSample.cpp)
#
# Tests subdirectories
#
add_subdirectory(TestSpace)
