# Find library
find_package(PkgConfig REQUIRED)
pkg_check_modules(JsonRpcCpp REQUIRED IMPORTED_TARGET libjsonrpccpp-server libjsonrpccpp-common libjsonrpccpp-client libjsonrpccpp-stub)
# Check if library was found and print info message
if (JsonRpcCpp_FOUND)
    message(STATUS "Found JsonRpcCpp library")
    message(STATUS "    libraries: ${JsonRpcCpp_LIBRARIES}")
    message(STATUS "    include path: ${JsonRpcCpp_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Could not find JsonRpcCpp library, try apt-get install libjsonrpccpp-dev")
endif ()