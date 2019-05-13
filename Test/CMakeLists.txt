cmake_minimum_required (VERSION 3.10)
project (Test)
# Configure google-test as a downloadable library.
include(GoogleTest.cmake)
#
function(add_gtests)
    set(options)
    set(oneValue   TARGET)
    set(multiValue INCLUDES SOURCES LINKS DEPENDS)
    cmake_parse_arguments(ARG "${options}" "${oneValue}" "${multiValue}" ${ARGN} )
    add_executable (${ARG_TARGET} ${ARG_SOURCES})
    # dependencies
    foreach(L ${ARG_LINKS})
        get_target_property(type ${L} TYPE)
        if(${type} EQUAL OBJECT_LIBRARY)
            target_sources(${ARG_TARGET} PUBLIC $<TARGET_OBJECTS:${L}>)
        endif()
    endforeach()
    target_include_directories(${ARG_TARGET}
        PRIVATE ${ARG_INCLUDES})
    target_link_libraries( ${ARG_TARGET}
        PRIVATE GTest::GTest GTest::Main ${ARG_DEPENDS})
    add_test(NAME ${ARG_TARGET} COMMAND ${ARG_TARGET})
endfunction()
#
# add Test sample
add_gtests(TARGET TestSample SOURCES TestSample.cpp)
#
# Tests subdirectories
#
add_subdirectory(TestLegacy)
add_subdirectory(TestShare)
add_subdirectory(TestSpace)
