function(create_build_info)
    # Generate header file containing useful build information
    add_custom_target(BuildInfo.h ALL
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND}
        -DBUILD_INFO_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
        -DBUILD_INFO_DST_DIR="${PROJECT_BINARY_DIR}"
        -DSAMPLE_BUILDINFO_IN="${PROJECT_SOURCE_DIR}/cmake/templates/BuildInfo.h.in"
        -DSAMPLE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
        -DSAMPLE_BUILD_OS="${CMAKE_SYSTEM_NAME}"
        -DSAMPLE_BUILD_COMPILER="${CMAKE_CXX_COMPILER_ID}"
        -DSAMPLE_BUILD_COMPILER_VERSION="${CMAKE_CXX_COMPILER_VERSION}"
        -DSAMPLE_VERSION_SUFFIX="${VERSION_SUFFIX}"
        -DPROJECT_VERSION="${PROJECT_VERSION}"
        -P "${PROJECT_SOURCE_DIR}/cmake/scripts/buildinfo.cmake"
        )
    include_directories(BEFORE ${PROJECT_BINARY_DIR})
endfunction()
