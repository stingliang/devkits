# Modify your Qt library prefix path here
#set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\msvc2019")
list(APPEND CMAKE_PREFIX_PATH ${QT_INSTALL_PATH})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

if (Qt5_FOUND)
    print_library_info("Qt" ${Qt5_VERSION} ${QT_INSTALL_PATH}/lib)
else()
    message (FATAL_ERROR "Cannot find Qt")
endif ()