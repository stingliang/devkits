file(GLOB SRC_LIST "*.h" "*.cpp")
# executable files
add_executable(test-transpond ${SRC_LIST})
# test deps
target_include_directories(test-transpond PUBLIC ${BOOST_INCLUDE_DIR})
target_link_libraries(test-transpond PUBLIC devcore network Boost::Thread Boost::UnitTestFramework)