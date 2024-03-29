#find_package(CURL REQUIRED)
# find_package(MHD REQUIRED)
set(CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -DCMAKE_BUILD_TYPE=Release
               # Build static lib but suitable to be included in a shared lib.
               -DCMAKE_POSITION_INDEPENDENT_CODE=${BUILD_SHARED_LIBS}
               -DBUILD_STATIC_LIBS=ON
               -DBUILD_SHARED_LIBS=OFF
               -DUNIX_DOMAIN_SOCKET_SERVER=OFF
               -DUNIX_DOMAIN_SOCKET_CLIENT=OFF
               -DHTTP_SERVER=ON
               -DHTTP_CLIENT=OFF
               -DCOMPILE_TESTS=OFF
               -DCOMPILE_STUBGEN=OFF
               -DCOMPILE_EXAMPLES=OFF
               # Point to jsoncpp library.
               -DJSONCPP_INCLUDE_DIR=${JSONCPP_INCLUDE_DIR}
               # Select jsoncpp include prefix: <json/...> or <jsoncpp/json/...>
               -DJSONCPP_INCLUDE_PREFIX=json
               -DJSONCPP_LIBRARY=${JSONCPP_LIBRARY}
            #    -DCURL_INCLUDE_DIR=${CURL_INCLUDE_DIR}
            #    -DCURL_LIBRARY=${CURL_LIBRARY}
               -DMHD_INCLUDE_DIR=${MHD_INCLUDE_DIR}
               -DMHD_LIBRARY=${MHD_LIBRARY}
            #    -DCMAKE_C_FLAGS=-fvisibility=hidden -fvisibility-inlines-hidden
            #    -DCMAKE_CXX_FLAGS=-fvisibility=hidden -fvisibility-inlines-hidden
               -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
               -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
               )


ExternalProject_Add(jsonrpccpp
    PREFIX ${CMAKE_SOURCE_DIR}/deps
    DOWNLOAD_NAME jsonrcpcpp-0.7.0.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    URL https://github.com/cinemast/libjson-rpc-cpp/archive/v0.7.0.tar.gz
        https://osp-1257653870.cos.ap-guangzhou.myqcloud.com/FISCO-BCOS/FISCO-BCOS/deps/jsonrcpcpp-0.7.0.tar.gz
        https://raw.githubusercontent.com/FISCO-BCOS/LargeFiles/master/libs/jsonrcpcpp-0.7.0.tar.gz
    URL_HASH SHA256=669c2259909f11a8c196923a910f9a16a8225ecc14e6c30e2bcb712bab9097eb
    # On Windows it tries to install this dir. Create it to prevent failure.
    PATCH_COMMAND ${CMAKE_COMMAND} -E make_directory <SOURCE_DIR>/win32-deps/include
    CMAKE_ARGS ${CMAKE_ARGS}
    LOG_CONFIGURE 1
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config Release
    INSTALL_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config Release --target install
    LOG_BUILD 1
    LOG_INSTALL 1
    BUILD_BYPRODUCTS ${CMAKE_SOURCE_DIR}/deps/lib/libjsonrpccpp-server.a ${CMAKE_SOURCE_DIR}/deps/lib/libjsonrpccpp-common.a
)

add_dependencies(jsonrpccpp jsoncpp)
add_dependencies(jsonrpccpp MHD)

ExternalProject_Get_Property(jsonrpccpp SOURCE_DIR)
ExternalProject_Get_Property(jsonrpccpp INSTALL_DIR)
set(JSONRPCCPP_INCLUDE_DIR ${SOURCE_DIR}/src)
file(MAKE_DIRECTORY ${JSONRPCCPP_INCLUDE_DIR})  # Must exist.

add_library(JsonRpcCpp::Common STATIC IMPORTED)
set_property(TARGET JsonRpcCpp::Common PROPERTY IMPORTED_LOCATION ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}jsonrpccpp-common${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET JsonRpcCpp::Common PROPERTY INTERFACE_LINK_LIBRARIES JsonCpp)
set_property(TARGET JsonRpcCpp::Common PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${JSONRPCCPP_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIR})
add_dependencies(JsonRpcCpp::Common jsonrpccpp)

# add_library(JsonRpcCpp::Client STATIC IMPORTED)
# set_property(TARGET JsonRpcCpp::Client PROPERTY IMPORTED_LOCATION ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}jsonrpccpp-client${CMAKE_STATIC_LIBRARY_SUFFIX})
# set_property(TARGET JsonRpcCpp::Client PROPERTY INTERFACE_LINK_LIBRARIES JsonRpcCpp::Common ${CURL_LIBRARY})
# set_property(TARGET JsonRpcCpp::Client PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CURL_INCLUDE_DIR})
# add_dependencies(JsonRpcCpp::Client jsonrpccpp)

add_library(JsonRpcCpp::Server STATIC IMPORTED)
set_property(TARGET JsonRpcCpp::Server PROPERTY IMPORTED_LOCATION ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}jsonrpccpp-server${CMAKE_STATIC_LIBRARY_SUFFIX})
set_property(TARGET JsonRpcCpp::Server PROPERTY INTERFACE_LINK_LIBRARIES JsonRpcCpp::Common MHD)
# set_property(TARGET JsonRpcCpp::Server PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${MHD_INCLUDE_DIR})
add_dependencies(JsonRpcCpp::Server jsonrpccpp)

unset(BINARY_DIR)
unset(INSTALL_DIR)
unset(CMAKE_ARGS)
