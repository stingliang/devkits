# Library name
set(LIBRARY_NAME initializer)

# Add all source files
file(GLOB SRC_LIST "*.h" "*.cpp")

# Generate the executable program
add_library(${LIBRARY_NAME} STATIC ${SRC_LIST})

# Include path
#target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

# Link components
target_link_libraries(${LIBRARY_NAME} PUBLIC devcore)

# Declare dependencies
add_dependencies(${LIBRARY_NAME} devcore)