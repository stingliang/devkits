# Find library
find_package(Boost REQUIRED COMPONENTS log regex system chrono random thread iostreams date_time filesystem serialization program_options unit_test_framework)
# Check if library was found
if(Boost_FOUND)
    # 打印一些有关Boost库的版本信息
    message(STATUS "Boost library status:")
    message(STATUS "    version: ${Boost_VERSION}")
    message(STATUS "    include path: ${Boost_INCLUDE_DIRS}")
    message(STATUS "    library path: ${Boost_LIBRARY_DIRS}")
    message(STATUS "    libraries:")
    foreach (Boost_LIB ${Boost_LIBRARIES})
        message(STATUS "        ${Boost_LIB}")
    endforeach()
    # 添加头文件搜索路径
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

