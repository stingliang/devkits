include(ExternalProject)
include(GNUInstallDirs)

ExternalProject_Add(mysqlclient
        PREFIX ${CMAKE_SOURCE_DIR}/deps
        DOWNLOAD_NAME mysql-connector-c-6.1.11-src.tar.gz
        DOWNLOAD_NO_PROGRESS 1
        BUILD_IN_SOURCE 1
        LOG_CONFIGURE 1
        LOG_BUILD 1
        LOG_INSTALL 1
        URL https://cdn.mysql.com/archives/mysql-connector-c/mysql-connector-c-6.1.11-src.tar.gz
        URL_HASH SHA256=c8664851487200162b38b6f3c8db69850bd4f0e4c5ff5a6d161dbfb5cb76b6c4
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/
        BUILD_BYPRODUCTS ${CMAKE_SOURCE_DIR}/deps/lib/libmysqlclient${CMAKE_STATIC_LIBRARY_SUFFIX}
        )
ExternalProject_Get_Property(mysqlclient SOURCE_DIR)

ExternalProject_Get_Property(mysqlclient INSTALL_DIR)

unset(INSTALL_DIR)