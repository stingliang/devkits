/**
 * @project Devkits
 * @file example.cpp
 * @author liangrui (liangrui5526@126.com)
 * @date 2022/10/25 23:49:57
 */

#include "BuildInfo.h"
#include "libinitializer/Initializer.h"

#include <boost/core/ignore_unused.hpp>

#define PROJECT_NAME "Devkits"

int main (int argc, const char* argv[]) {

    boost::ignore_unused(argc, argv);

    try {
        printVersion(PROJECT_NAME);
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}