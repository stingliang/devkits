if(UNIX)
    # Create include and libraries directory
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/deps/include/)  # Must exist.
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/deps/lib/)  # Must exist.

    # Requirements of compiler
    set(REQUIRED_COMPILER_VERSION 7.4)
    if (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER ${REQUIRED_COMPILER_VERSION}
            OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL ${REQUIRED_COMPILER_VERSION}))
        message(FATAL_ERROR
                "${PROJECT_NAME} requires g++ ${REQUIRED_COMPILER_VERSION} or greater."
                "Current is ${CMAKE_CXX_COMPILER_VERSION}")
    endif ()

    # Compiler flags and options
    set(CMAKE_CXX_FLAGS "-pthread -fPIC -fvisibility=hidden -fvisibility-inlines-hidden -fexceptions")
    add_compile_options(-Werror)
    add_compile_options(-Wall)
    add_compile_options(-pedantic)
    add_compile_options(-Wextra)
    # add_compile_options(-Wno-unused-variable)
    # add_compile_options(-Wno-unused-parameter)
    # add_compile_options(-Wno-unused-function)
    # add_compile_options(-Wno-missing-field-initializers)
    # Disable warnings about unknown pragmas (which is enabled by -Wall).
    add_compile_options(-Wno-unknown-pragmas)
    add_compile_options(-fno-omit-frame-pointer)
endif()

macro(add_library_info OPT DEF)
    if (DEFINED ${OPT})
        if (${${OPT}})
            set(${OPT} ON)
        else ()
            set(${OPT} OFF)
        endif()
    else ()
        set(${OPT} ${DEF})
    endif()
endmacro()

macro(default_option OPT DEF)
    if (DEFINED ${OPT})
        if (${${OPT}})
            set(${OPT} ON)
        else ()
            set(${OPT} OFF)
        endif()
    else ()
        set(${OPT} ${DEF})
    endif()
endmacro()

macro(configure_project)
    # Unit tests
    default_option(TESTS OFF)
    # Mini demos
    default_option(DEMO OFF)
    # Tools
    default_option(TOOL OFF)
    # Gui components
    default_option(WITH_GUI OFF)

    print_config()

endmacro()

macro(print_config)
    message("------------------------------------------------------------------------")
    message("-- Configuring   ${PROJECT_NAME} ${PROJECT_VERSION}")
    message("------------------------------------------------------------------------")
    message("-- CMake         Cmake version and location   ${CMAKE_VERSION}")
    message("-- Compiler      C++ compiler version         ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    message("-- Build type    Target type                  ${CMAKE_BUILD_TYPE}")
    message("-- Platform      Target platform              ${CMAKE_SYSTEM_NAME}")
    message("------------------------------------------------------------------------")
    message("-- Test          Unit tests                   ${TESTS}")
    message("-- Demo          Libraries usage demo         ${DEMO}")
    message("-- Tool          Utility tools                ${TOOL}")
    message("-- Gui           Compile GUI components       ${WITH_GUI}")
    message("------------------------------------------------------------------------")
endmacro()

macro(print_library_info LIBRARY_NAME LIBRARY_VERSION)
    message("------------------------------------------------------------------------")
    message("-- Library       ${LIBRARY_NAME}")
    message("-- Version       ${LIBRARY_VERSION}")
#    message("------------------------------------------------------------------------")
endmacro()
