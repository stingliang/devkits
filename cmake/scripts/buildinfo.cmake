#------------------------------------------------------------------------------
# generates BuildInfo.h
# ------------------------------------------------------------------------------

macro(replace_if_different SOURCE DST)
    set(extra_macro_args ${ARGN})
    set(options CREATE)
    set(one_value_args)
    set(multi_value_args)
    cmake_parse_arguments(REPLACE_IF_DIFFERENT "${options}" "${one_value_args}" "${multi_value_args}" "${extra_macro_args}")

    if (REPLACE_IF_DIFFERENT_CREATE AND (NOT (EXISTS "${DST}")))
        file(WRITE "${DST}" "")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files "${SOURCE}" "${DST}" RESULT_VARIABLE DIFFERENT OUTPUT_QUIET ERROR_QUIET)

    if (DIFFERENT)
        execute_process(COMMAND ${CMAKE_COMMAND} -E rename "${SOURCE}" "${DST}")
    else()
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove "${SOURCE}")
    endif()
endmacro()

if (NOT SAMPLE_BUILD_TYPE)
    set(SAMPLE_BUILD_TYPE "unknown")
endif()

if (NOT SAMPLE_BUILD_PLATFORM)
    set(SAMPLE_BUILD_PLATFORM "unknown")
endif()

execute_process(
    COMMAND git --git-dir=${CMAKE_SOURCE_DIR}/.git --work-tree=${CMAKE_SOURCE_DIR} rev-parse HEAD
    OUTPUT_VARIABLE SAMPLE_COMMIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
) 

if (NOT SAMPLE_COMMIT_HASH)
    set(SAMPLE_COMMIT_HASH 0)
endif()

execute_process(
    COMMAND date "+%Y%m%d %H:%M:%S" 
    OUTPUT_VARIABLE SAMPLE_BUILD_TIME OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
    )

execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD 
    OUTPUT_VARIABLE SAMPLE_BUILD_BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
    )

set(TMPFILE "${CMAKE_BINARY_DIR}/BuildInfo.h.tmp")
set(OUTFILE "${CMAKE_BINARY_DIR}/BuildInfo.h")

configure_file("${SAMPLE_BUILDINFO_IN}" "${TMPFILE}")

replace_if_different("${TMPFILE}" "${OUTFILE}" CREATE)

