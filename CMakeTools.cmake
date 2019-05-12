# -------------------------------------------------------------------------------------------------
# create container
# -------------------------------------------------------------------------------------------------
function(create_container)
    set(options)
    set(oneValue   TARGET)
    set(multiValue SOURCES PUBLIC_INCLUDES PRIVATE_INCLUDES PUBLIC_LINKS PRIVATE_LINKS)
    cmake_parse_arguments(ARG "${options}" "${oneValue}" "${multiValue}" ${ARGN} )
    # object library
    add_library(${ARG_TARGET} OBJECT ${ARG_SOURCES})
    # dependencies
    target_include_directories(${ARG_TARGET} 
        PUBLIC  ${ARG_PUBLIC_INCLUDES}
        PRIVATE ${ARG_PRIVATE_INCLUDES})
    foreach(L ${ARG_PUBLIC_LINKS})
        target_include_directories(${ARG_TARGET} 
            PUBLIC $<TARGET_PROPERTY:${L},INTERFACE_INCLUDE_DIRECTORIES>)
    endforeach()
    foreach(L ${ARG_PRIVATE_LINKS})
        target_include_directories(${ARG_TARGET} 
            PRIVATE $<TARGET_PROPERTY:${L},INTERFACE_INCLUDE_DIRECTORIES>)
    endforeach()
endfunction()
# -------------------------------------------------------------------------------------------------
# create interface
# -------------------------------------------------------------------------------------------------
function(create_interface)
    set(options)
    set(oneValue   TARGET)
    set(multiValue INCLUDES LINKS)
    cmake_parse_arguments(ARG "${options}" "${oneValue}" "${multiValue}" ${ARGN} )
    # object library
    add_library(${ARG_TARGET} OBJECT)
    # dependencies
    target_include_directories(${ARG_TARGET} 
        PUBLIC ${ARG_INCLUDES})
    foreach(L ${ARG_LINKS})
        target_include_directories(${ARG_TARGET} 
            PUBLIC $<TARGET_PROPERTY:${L},INTERFACE_INCLUDE_DIRECTORIES>)
        target_sources(${ARG_TARGET} 
            PUBLIC $<TARGET_OBJECTS:${L}>)
    endforeach()
endfunction()
# -------------------------------------------------------------------------------------------------
# create library
# -------------------------------------------------------------------------------------------------
function(create_library)
    set(options)
    set(oneValue   TARGET)
    set(multiValue SOURCES PUBLIC_INCLUDES PRIVATE_INCLUDES PUBLIC_LINKS PRIVATE_LINKS)
    cmake_parse_arguments(ARG "${options}" "${oneValue}" "${multiValue}" ${ARGN} )
    # object library
    add_library(${ARG_TARGET}
        ${ARG_SOURCES}
    )
    # dependencies
    target_include_directories(${ARG_TARGET} 
    PUBLIC
        ${ARG_PUBLIC_INCLUDES}
    PRIVATE
        ${ARG_PRIVATE_INCLUDES}
    )
    foreach(L ${ARG_PUBLIC_LINKS})
        target_include_directories(${ARG_TARGET} 
        PUBLIC 
            $<TARGET_PROPERTY:${L},INTERFACE_INCLUDE_DIRECTORIES>
        )
    endforeach()
    foreach(L ${ARG_PRIVATE_LINKS})
        target_include_directories(${ARG_TARGET} 
        PRIVATE 
            $<TARGET_PROPERTY:${L},INTERFACE_INCLUDE_DIRECTORIES>
        )
    endforeach()
endfunction()

# -------------------------------------------------------------------------------------------------
# create executable
# -------------------------------------------------------------------------------------------------
function(create_executable)
    set(options)
    set(oneValue   TARGET)
    set(multiValue SOURCES INCLUDES LINKS)
    cmake_parse_arguments(ARG "${options}" "${oneValue}" "${multiValue}" ${ARGN} )
    # executable
    add_executable(${ARG_TARGET} ${ARG_SOURCES})
    # dependencies
    target_include_directories(${ARG_TARGET} 
        PRIVATE ${ARG_INCLUDES})
    foreach(L ${ARG_LINKS})
        target_include_directories(${ARG_TARGET} 
            PRIVATE $<TARGET_PROPERTY:${L},INTERFACE_INCLUDE_DIRECTORIES>)
        target_sources(${ARG_TARGET} 
            PUBLIC $<TARGET_OBJECTS:${L}>)
    endforeach()
endfunction()
# -------------------------------------------------------------------------------------------------
# End
# -------------------------------------------------------------------------------------------------