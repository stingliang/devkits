if(UNIX)
    # Create include and libraries directory
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/deps/include/)  # Must exist.
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/deps/lib/)  # Must exist.

    # Requirements of compiler
    set(REQUIRED_COMPLIER_VERSION 7.4)
    if (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER ${REQUIRED_COMPLIER_VERSION}
            OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL ${REQUIRED_COMPLIER_VERSION}))
        message(FATAL_ERROR
                "${PROJECT_NAME} requires g++ ${REQUIRED_COMPLIER_VERSION} or greater."
                "Current is ${CMAKE_CXX_COMPILER_VERSION}")
    endif ()
elseif(WIN32)
    # do nothing
endif()

# Generate build information
include(BuildInfo)
create_build_info()

macro(configure_project)
    message("")
    message("------------------------------------------------------------------------")
    message("-- Configuring   ${PROJECT_NAME} ${PROJECT_VERSION}")
    message("------------------------------------------------------------------------")
    message("-- CMake         Cmake version and location   ${CMAKE_VERSION}")
    message("-- Compiler      C++ compiler version         ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    message("-- Build type    Target type                  ${CMAKE_BUILD_TYPE}")
    message("-- Platform      Target platform              ${CMAKE_SYSTEM_NAME}")
    message("------------------------------------------------------------------------")
    message("")
endmacro()
