# Library name
set(LIBRARY_NAME devcore)

# Add all source files
file(GLOB SRC_LIST "*.h" "*.cpp")

# Generate the executable program
add_library(${LIBRARY_NAME} STATIC ${SRC_LIST})

# Link components
target_link_libraries(${LIBRARY_NAME} PUBLIC Boost::log Boost::system)

# Declare dependencies
add_dependencies(${LIBRARY_NAME} BuildInfo.h Boost::boost Boost::log Boost::system)
