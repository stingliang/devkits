# Cmake minimum version requirements
cmake_minimum_required(VERSION 3.0)

# Set cmake scripts folder path so that cmake could find the scripts, later, you can use include() command
set(DEVKITS_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake scripts folder")
list(APPEND CMAKE_MODULE_PATH ${DEVKITS_CMAKE_DIR})

# Project name and version, replace it with your own project version
project(Devkits VERSION "2.0.0")

# Required cpp library version
set(CMAKE_CXX_STANDARD 14)

include(Options)
include(ProjectBoost)
configure_project()

include_directories("${CMAKE_SOURCE_DIR}")

# Load libs
#if (${Boost_FOUND})
#    add_definitions(-DBOOST_ALL_DYN_LINK)
#endif()

#add_subdirectory(libdevcore)
add_subdirectory(main)

# Unit test settings
enable_testing()
add_subdirectory(test)