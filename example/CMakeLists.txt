# libdevcore demo
add_executable(libdevcore_demo libdevcore_demo.cpp)
target_link_libraries(libdevcore_demo devcore)
add_dependencies(libdevcore_demo devcore Boost::log)