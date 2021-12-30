if (LOCAL_COMPILATION_BOOST)
    include(ExternalProject)
    include(GNUInstallDirs)

    include(ProcessorCount)
    ProcessorCount(CORES)
    if(CORES EQUAL 0)
        set(CORES 1)
    elseif(CORES GREATER 2)
        set(CORES 2)
    endif()

    set(SED_CMMAND sed -i)
    set(BOOST_BOOTSTRAP_COMMAND ./bootstrap.sh)

    set(BOOST_INSTALL_COMMAND ./b2 install --prefix=${CMAKE_SOURCE_DIR}/deps)
    set(BOOST_BUILD_TOOL ./b2)
    set(BOOST_LIBRARY_SUFFIX .a)

    set(BOOST_LIB_PREFIX ${CMAKE_SOURCE_DIR}/deps/src/boost/stage/lib/libboost_)
    set(BOOST_BUILD_FILES ${BOOST_LIB_PREFIX}chrono.a ${BOOST_LIB_PREFIX}date_time.a
            ${BOOST_LIB_PREFIX}random.a ${BOOST_LIB_PREFIX}regex.a
            ${BOOST_LIB_PREFIX}filesystem.a ${BOOST_LIB_PREFIX}system.a
            ${BOOST_LIB_PREFIX}unit_test_framework.a ${BOOST_LIB_PREFIX}log.a
            ${BOOST_LIB_PREFIX}thread.a ${BOOST_LIB_PREFIX}program_options.a
            ${BOOST_LIB_PREFIX}serialization.a)

    ExternalProject_Add(boost
            PREFIX ${CMAKE_SOURCE_DIR}/deps
            DOWNLOAD_NO_PROGRESS 1
            URL https://udomain.dl.sourceforge.net/project/boost/boost/1.58.0/boost_1_58_0.tar.bz2
            URL_HASH SHA256=fdfc204fc33ec79c99b9a74944c3e54bd78be4f7f15e260c0e2700a36dc7d3e5
            BUILD_IN_SOURCE 1
            CONFIGURE_COMMAND ${BOOST_BOOTSTRAP_COMMAND}
            BUILD_COMMAND ${BOOST_BUILD_TOOL} stage
            ${BOOST_CXXFLAGS}
            threading=multi
            link=static
            variant=release
            address-model=64
            --with-chrono
            --with-date_time
            --with-filesystem
            --with-system
            --with-random
            --with-regex
            --with-test
            --with-thread
            --with-serialization
            --with-program_options
            --with-log
            --with-iostreams
            -s NO_BZIP2=1 -s NO_LZMA=1 -s NO_ZSTD=1
            -j${CORES}
            LOG_CONFIGURE 1
            LOG_BUILD 1
            LOG_INSTALL 1
            INSTALL_COMMAND ""
            # INSTALL_COMMAND ${BOOST_INSTALL_COMMAND}
            BUILD_BYPRODUCTS ${BOOST_BUILD_FILES}
            )

    ExternalProject_Get_Property(boost SOURCE_DIR)
    set(BOOST_INCLUDE_DIR ${SOURCE_DIR})
    set(BOOST_LIB_DIR ${SOURCE_DIR}/stage/lib)

else()
    find_package(Boost 1.58 REQUIRED COMPONENTS
            filesystem system chrono date_time unit_test_framework log
            program_options thread serialization iostreams regex random)

    # check if boost was found
    if(Boost_FOUND)
        message ("boost found")
    else()
        message (FATAL_ERROR "Cannot find Boost")
    endif()

    set(BOOST_INCLUDE_DIR ${Boost_INCLUDE_DIRS})
    set(BOOST_LIB_DIR ${Boost_LIBRARY_DIRS})
    set(BOOST_LIBRARY_SUFFIX .so)

endif ()

    add_library(Boost::System STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::System PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_system${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::System PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    add_dependencies(Boost::System boost)

    add_library(Boost::Chrono STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Chrono PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_chrono${BOOST_LIBRARY_SUFFIX})
    add_dependencies(Boost::Chrono boost)

    add_library(Boost::DataTime STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::DataTime PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_date_time${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::DataTime PROPERTY INTERFACE_LINK_LIBRARIES Boost::System)
    add_dependencies(Boost::DataTime boost)

    add_library(Boost::Regex STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Regex PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_regex${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::Regex PROPERTY INTERFACE_LINK_LIBRARIES Boost::System)
    add_dependencies(Boost::Regex boost)

    add_library(Boost::Filesystem STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Filesystem PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_filesystem${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::Filesystem PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    set_property(TARGET Boost::Filesystem PROPERTY INTERFACE_LINK_LIBRARIES Boost::System)
    add_dependencies(Boost::Filesystem boost)

    add_library(Boost::Random STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Random PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_random${BOOST_LIBRARY_SUFFIX})
    add_dependencies(Boost::Random boost)

    add_library(Boost::UnitTestFramework STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::UnitTestFramework PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_unit_test_framework${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::UnitTestFramework PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    add_dependencies(Boost::UnitTestFramework boost)

    add_library(Boost::Thread STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Thread PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_thread${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::Thread PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    set_property(TARGET Boost::Thread PROPERTY INTERFACE_LINK_LIBRARIES Boost::Chrono Boost::DataTime Boost::Regex)
    add_dependencies(Boost::Thread boost)

    add_library(Boost::Program_options STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Program_options PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_program_options${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::Program_options PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    add_dependencies(Boost::Program_options boost)

    add_library(Boost::Log STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Log PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_log${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::Log PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    set_property(TARGET Boost::Log PROPERTY INTERFACE_LINK_LIBRARIES Boost::Filesystem Boost::Thread)
    add_dependencies(Boost::Log boost)

    add_library(Boost::Serialization STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Serialization PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_serialization${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::Serialization PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    add_dependencies(Boost::Serialization boost)

    # for boost compress/base64encode
    add_library(Boost::Iostreams STATIC IMPORTED GLOBAL)
    set_property(TARGET Boost::Iostreams PROPERTY IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_iostreams${BOOST_LIBRARY_SUFFIX})
    set_property(TARGET Boost::Iostreams PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${BOOST_INCLUDE_DIR})
    add_dependencies(Boost::Iostreams boost)
    unset(SOURCE_DIR)


