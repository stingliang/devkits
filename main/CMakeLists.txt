file(GLOB SRC_LIST "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC devcore Boost::Program_options Boost::Log pthread)