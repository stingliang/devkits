file(GLOB SRC_LIST "*.cpp")
file(GLOB HEADERS "*.h")

if (${Boost_FOUND})
    add_library(devcore SHARED ${SRC_LIST} ${HEADERS})
else()
    add_library(devcore ${SRC_LIST} ${HEADERS})
endif ()

target_include_directories(devcore SYSTEM BEFORE PUBLIC ${BOOST_INCLUDE_DIR})
target_compile_options(devcore PRIVATE -Wno-error -Wno-unused-variable)
target_link_libraries(devcore PUBLIC Boost::Log Boost::System Boost::Filesystem Boost::DataTime Boost::Thread pthread)