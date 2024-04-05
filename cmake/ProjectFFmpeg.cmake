# Find library
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
        libavdevice libavformat libavfilter libavcodec libswscale libswresample libavutil)
# Check if library was found and print info message
if (FFMPEG_FOUND)
    message(STATUS "FFmpeg library status:")
    message(STATUS "    libraries: ${FFMPEG_LIBRARIES}")
    message(STATUS "    include path: ${FFMPEG_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR
            "Could not find FFMPEG library, try apt-get install libavcodec-dev
            libavformat-dev libavutil-dev libswscale-dev libswresample-dev libavdevice-dev")
endif ()
