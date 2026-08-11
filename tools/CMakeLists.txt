file(GLOB TOOL_DIRECTORIES
    LIST_DIRECTORIES true
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/tools/*"
)

set(TOOLS)

foreach(TOOL_DIRECTORY ${TOOL_DIRECTORIES})
    if (NOT IS_DIRECTORY "${TOOL_DIRECTORY}")
        continue()
    endif()

    get_filename_component(
        TOOL_NAME
        "${TOOL_DIRECTORY}"
        NAME
    )

    if (TOOL_NAME STREQUAL "external")
        continue()
    endif()

    file(GLOB_RECURSE TOOL_SOURCES
        CONFIGURE_DEPENDS
        "${TOOL_DIRECTORY}/*.cpp"
    )

    if (NOT TOOL_SOURCES)
        continue()
    endif()

    message(STATUS "Found tool: ${TOOL_NAME}")

    add_executable(
        ${TOOL_NAME}
        ${TOOL_SOURCES}
    )

    target_include_directories(
        ${TOOL_NAME}
        PRIVATE
        "${CMAKE_SOURCE_DIR}/tools/external"
    )

    list(APPEND TOOLS ${TOOL_NAME})
endforeach()

set(RUN_TOOL_COMMANDS)

foreach(TOOL ${TOOLS})
    list(APPEND
        RUN_TOOL_COMMANDS
        COMMAND $<TARGET_FILE:${TOOL}>
    )
endforeach()

add_custom_target(run_tools
    ${RUN_TOOL_COMMANDS}

    WORKING_DIRECTORY
        "${CMAKE_SOURCE_DIR}"

    DEPENDS
        ${TOOLS}

    COMMENT
        "Running tools"

    VERBATIM
)
