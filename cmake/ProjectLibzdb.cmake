include(ExternalProject)

include(ProjectMysqlClient)
include(ProjectSQLite3)

set(ZDB_CONFIGURE_COMMAND
        ./configure --with-mysql=${SOURCE_DIR}/scripts/mysql_config --with-sqlite
        --without-postgresql --enable-shared=false --enable-protected)

ExternalProject_Add(libzdb DEPENDS mysqlclient sqlite
    PREFIX ${CMAKE_SOURCE_DIR}/deps
    DOWNLOAD_NAME libzdb-3.2.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    URL https://tildeslash.com/libzdb/dist/libzdb-3.2.tar.gz
    URL_HASH SHA256=005ddf4b29c6db622e16303298c2f914dfd82590111cea7cfd09b4acf46cf4f2
    BUILD_IN_SOURCE 1
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
    CONFIGURE_COMMAND ${ZDB_CONFIGURE_COMMAND}
    BUILD_COMMAND make
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS <SOURCE_DIR>/.libs/libzdb${CMAKE_STATIC_LIBRARY_SUFFIX}
)
add_dependencies(libzdb mysqlclient sqlite)

ExternalProject_Get_Property(libzdb SOURCE_DIR)

add_library(zdb STATIC IMPORTED GLOBAL)
set(LIBZDB_INCLUDE_DIR ${SOURCE_DIR}/zdb/)
set(LIBZDB_LIBRARY ${SOURCE_DIR}/.libs/libzdb${CMAKE_STATIC_LIBRARY_SUFFIX})
file(MAKE_DIRECTORY ${LIBZDB_INCLUDE_DIR})  # Must exist.

set_property(TARGET zdb PROPERTY IMPORTED_LOCATION ${LIBZDB_LIBRARY})
set_property(TARGET zdb PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${LIBZDB_INCLUDE_DIR})
set_property(TARGET zdb PROPERTY INTERFACE_LINK_LIBRARIES  mysqlclient sqlite z)
add_dependencies(zdb libzdb mysqlclient sqlite)

unset(SOURCE_DIR)
