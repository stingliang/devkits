# Find library
find_package(Boost REQUIRED COMPONENTS
        log
        regex
        system
        chrono
        random
        thread
        iostreams
        date_time
        filesystem
        serialization
        program_options
        unit_test_framework)

# Check if library was found
if(Boost_FOUND)
    print_library_info("Boost" ${Boost_VERSION_STRING} ${Boost_LIBRARY_DIRS})
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

