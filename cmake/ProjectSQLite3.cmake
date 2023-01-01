include(ExternalProject)
include(GNUInstallDirs)

set(SQLITE_CMAKE_COMMAND ./configure --enable-static
                                     --disable-shared
                                     --disable-tcl
                                     --with-gnu-ld
                                     --prefix=${CMAKE_SOURCE_DIR}/deps)

ExternalProject_Add(sqlite
        PREFIX ${CMAKE_SOURCE_DIR}/deps
        DOWNLOAD_NAME sqlite3.tar.gz
        DOWNLOAD_NO_PROGRESS 1
        URL https://www.sqlite.org/src/tarball/3bfa9cc9/SQLite-3bfa9cc9.tar.gz
        URL_HASH SHA256=1cd56ea9c5fe194290dc97c0955a3f8f6b1933c15db6f8e710b2b83e4eb83910
        CONFIGURE_COMMAND ${SQLITE_CMAKE_COMMAND}
        BUILD_IN_SOURCE 1
        LOG_CONFIGURE 1
        LOG_BUILD 1
        LOG_INSTALL 1
        INSTALL_COMMAND
        BUILD_BYPRODUCTS ${CMAKE_SOURCE_DIR}/deps/lib/libsqlite3${CMAKE_STATIC_LIBRARY_SUFFIX}
        )

ExternalProject_Get_Property(sqlite INSTALL_DIR)

unset(INSTALL_DIR)