# Cmake minimum version requirements
cmake_minimum_required(VERSION 3.0)

# Set cmake scripts folder path so that cmake could find the scripts, later, you can use include() command
set(DEVKITS_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake scripts folder")
list(APPEND CMAKE_MODULE_PATH ${DEVKITS_CMAKE_DIR})

# Project name and version, replace it with your own project version
project(Devkits VERSION "2.1.0")

# Required cpp library version
set(CMAKE_CXX_STANDARD 14)

# set default build type as Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# set default binary and library output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/${CMAKE_BUILD_TYPE}/lib)

# Generate build information
include(BuildInfo)
create_build_info()

# Load options
include(Options)

# Third part libraries
include(ProjectBoost)
# GUI components
if (WITH_GUI)
    include(ProjectQt)
    add_subdirectory(libgui)
endif()

# Print info
configure_project()

# Add project path to include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(libdevcore)
add_subdirectory(libinitializer)

# Demo
if (DEMO)
    add_subdirectory(example)
endif()

# Unit test settings
if (TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
