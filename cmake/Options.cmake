# Boost library settings
option (LOCAL_COMPILATION_BOOST "Compile boost current" OFF)
if (LOCAL_COMPILATION_BOOST)
    add_definitions(-DLOCAL_BOOST)
endif()

# Generate include and libraries directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/deps/include/)  # Must exist.
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/deps/lib/)  # Must exist.

# Requirements of compiler
if (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.4 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 5.4))
    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 5.4 or greater. Current is ${CMAKE_CXX_COMPILER_VERSION}")
endif ()

# Generate build information
include(BuildInfo)
create_build_info()

macro(configure_project)
    message("")
    message("------------------------------------------------------------------------")
    message("-- Configuring ${PROJECT_NAME} ${PROJECT_VERSION}")
    message("------------------------------------------------------------------------")
    message("-- CMake              Cmake version and location   ${CMAKE_VERSION} (${CMAKE_COMMAND})")
    message("-- Compiler           C++ compiler version         ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    message("-- Build type         Target type                  ${CMAKE_BUILD_TYPE}")
    message("-- Platform           Target platform              ${CMAKE_SYSTEM_NAME}")
    message("------------------------------------------------------------------------")
    message("-- Boost library information")
    message("--                    LOCAL_COMPILATION_BOOST      ${LOCAL_COMPILATION_BOOST}")
if (${Boost_FOUND})
    message("--                    Version                      ${Boost_LIB_VERSION}")
endif ()
    message("--                    Include path                 ${BOOST_INCLUDE_DIR}")
    message("--                    Library path                 ${BOOST_LIB_DIR}")
    message("--                    Link type                    ${BOOST_LIBRARY_SUFFIX}")
    message("------------------------------------------------------------------------")
    message("")
endmacro()