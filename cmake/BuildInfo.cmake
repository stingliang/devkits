function(create_build_info)
    # Set build platform; to be written to BuildInfo.h
    set(BUILD_OS "${CMAKE_SYSTEM_NAME}")

    # Select compiler
    if (CMAKE_COMPILER_IS_MINGW)
        set(BUILD_COMPILER "mingw")
    elseif (CMAKE_COMPILER_IS_MSYS)
        set(BUILD_COMPILER "msys")
    elseif (CMAKE_COMPILER_IS_GNUCXX)
        set(BUILD_COMPILER "g++")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(BUILD_COMPILER "clang")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
        set(BUILD_COMPILER "appleclang")
    else ()
        set(BUILD_COMPILER "unknown")
    endif ()

    # Set build type
    if (CMAKE_BUILD_TYPE)
        set(_cmake_build_type ${CMAKE_BUILD_TYPE})
    else()
        set(_cmake_build_type "${CMAKE_CFG_INTDIR}")
    endif()

    # Set build platform
    set(BUILD_PLATFORM "${BUILD_OS}/${BUILD_COMPILER}")

    # Generate header file containing useful build information
    add_custom_target(BuildInfo.h ALL
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND}
        -DSAMPLE_BUILDINFO_IN="${PROJECT_SOURCE_DIR}/cmake/templates/BuildInfo.h.in"
        -DSAMPLE_BUILD_TYPE="${_cmake_build_type}"
        -DSAMPLE_BUILD_OS="${BUILD_OS}"
        -DSAMPLE_BUILD_COMPILER="${BUILD_COMPILER}"
        -DSAMPLE_BUILD_PLATFORM="${BUILD_PLATFORM}"
        -DSAMPLE_VERSION_SUFFIX="${VERSION_SUFFIX}"
        -DPROJECT_VERSION="${PROJECT_VERSION}"
        -P "${PROJECT_SOURCE_DIR}/cmake/scripts/buildinfo.cmake"
        )
    include_directories(BEFORE ${PROJECT_BINARY_DIR})
    message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
    message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
    message(STATUS "CmakeScript = ${PROJECT_SOURCE_DIR}/cmake/scripts/buildinfo.cmake")
endfunction()
