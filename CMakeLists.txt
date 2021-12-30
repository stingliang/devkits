# cmake minimum version requirements
cmake_minimum_required(VERSION 3.0)

set(STS_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${STS_CMAKE_DIR})

# project name
project(sample VERSION "1.1.0")

# cpp version
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)

include(Options)
include(ProjectBoost)
configure_project()

include_directories("${CMAKE_SOURCE_DIR}")

# load libs
if (${Boost_FOUND})
    add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

add_subdirectory(libdevcore)
add_subdirectory(main)

# for unit test
enable_testing()
add_subdirectory(test)