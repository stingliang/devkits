# Executable program file name
set(PROGRAM_NAME main)

# Add all source files
file(GLOB SRC_LIST "*.h" "*.cpp")

# Generate the executable program
add_executable(${PROGRAM_NAME} ${SRC_LIST})

# Include path
#target_include_directories(${PROGRAM_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

# Link components
target_link_libraries(${PROGRAM_NAME} PUBLIC devcore)

# Declare dependencies
add_dependencies(${PROGRAM_NAME} devcore)