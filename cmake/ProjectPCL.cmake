find_package(PCL 1.8 REQUIRED)

# check if boost was found
if(PCL_FOUND)
    message ("Found PCL")
else()
    message (FATAL_ERROR "Cannot find PCL")
endif()

include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})
