/**
 * @project Devkits
 * @file main.cpp
 * @author liangrui (liangrui5526@126.com)
 * @date 2022/10/25 23:49:57
 */

#include "BuildInfo.h"
#include "libdevcore/Log.h"

#include <boost/core/ignore_unused.hpp>

#define PROJECT_NAME "Devkits"
#define MAIN_LOG(SEVERITY) LOGGER("Devkits", SEVERITY)

int main (int argc, const char* argv[]) {

    boost::ignore_unused(argc, argv);

    auto config = dev::log_initializer::log_config();
    config.severity = boost::log::trivial::info;
    dev::log_initializer::init(config);

    MAIN_LOG(info) << "This is a info log";

    try {
        printVersion(PROJECT_NAME);
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}