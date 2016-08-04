
set(CUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB items RELATIVE "${CUR_DIR}" "${CUR_DIR}/*")
foreach(suite ${items})
    if(IS_DIRECTORY "${CUR_DIR}/${suite}")
        list(APPEND suites ${suite})
        file(GLOB units RELATIVE "${CUR_DIR}/${suite}" "${CUR_DIR}/${suite}/*")
        foreach(unit ${units})
            list(APPEND ${suite} ${unit})
        endforeach()
    endif()
endforeach()
list(REMOVE_ITEM suites res)

foreach(suite ${suites})
    add_custom_target(${suite}
        COMMAND ln -sf ${CUR_DIR}/res/ ${BIN_DIR}/${suite})
    foreach(unit ${${suite}})
        file(GLOB sources
            "${CUR_DIR}/${suite}/${unit}/*.h"
            "${CUR_DIR}/${suite}/${unit}/*.cpp"
        )
        add_executable(${unit} ${sources})
        add_dependencies(${unit} ${suite})
        set_target_properties(${unit} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/${suite}")
        target_link_libraries(${unit} ${LIBS})

        file(GLOB shaders
            "${CUR_DIR}/${suite}/${unit}/*.vs"
            "${CUR_DIR}/${suite}/${unit}/*.frag"
            "${CUR_DIR}/${suite}/${unit}/*.gs"
        )
        foreach(shader ${shaders})
            get_filename_component(fname ${shader} NAME)
            set(output ${BIN_DIR}/${suite}/${fname})
            configure_file(${shader} ${output} COPYONLY)
        endforeach(shader)

        add_custom_target(${suite}-${unit}
            COMMAND "${unit}"
            WORKING_DIRECTORY "${BIN_DIR}/${suite}"
            DEPENDS ${unit}
        )
    endforeach()
endforeach()

