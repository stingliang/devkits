# Try to find the yaml-cpp library
find_package(yaml-cpp REQUIRED)
# Check if the library was found
if (yaml-cpp_FOUND)
    # Print some version information about the yaml-cpp library
    message(STATUS "yaml-cpp library status:")
    message(STATUS "    version: ${yaml-cpp_VERSION}")
    message(STATUS "    include path: /usr/include")
    message(STATUS "    library path: ${YAML_CPP_LIBRARIES}")
else ()
    # Print an error message if the library couldn't be found
    message(FATAL_ERROR "Cannot find yaml-cpp")
endif ()