
set(SUITES
    basic)

set(basic
    hello
    shader)

set(CUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

foreach(suite ${SUITES})
    foreach(unit ${${suite}})
        file(GLOB sources
            "${CUR_DIR}/${suite}/${unit}/*.h"
            "${CUR_DIR}/${suite}/${unit}/*.cpp"
        )
        add_executable(${unit} ${sources})
        set_target_properties(${unit} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/${suite}")
        target_link_libraries(${unit} ${LIBS})

        file(GLOB shaders
            "${CUR_DIR}/${suite}/${unit}/*.vs"
            "${CUR_DIR}/${suite}/${unit}/*.frag"
            "${CUR_DIR}/${suite}/${unit}/*.gs"
        )
        foreach(shader ${shaders})
            file(COPY ${shader} DESTINATION "${BIN_DIR}/${suite}")
        endforeach(shader)

        add_custom_target(${suite}-${unit}
            COMMAND "${unit}"
            WORKING_DIRECTORY "${BIN_DIR}/${suite}"
            DEPENDS ${unit}
        )
    endforeach(unit)
endforeach(suite)

