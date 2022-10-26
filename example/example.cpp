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
#define MAIN_LOG(LEVEL) LOG(LEVEL) << "[MAIN]"

void sampleLog() {
    MAIN_LOG(TRACE) << "This is a trace log";
    MAIN_LOG(DEBUG) << "This is a debug log";
    MAIN_LOG(INFO) << "This is a info log";
    MAIN_LOG(WARNING) << "This is a warning log";
    MAIN_LOG(ERROR) << "This is a error log";
//    MAIN_LOG(FATAL) << "This is a fatal log"; /**< It will cause coredump */
    MAIN_LOG(INFO) << LOG_KV("Component", "example") << "This is a key-value log";
}

int main (int argc, const char* argv[]) {

    boost::ignore_unused(argc, argv);

    // initialize all components
    auto initialize = std::make_shared<dev::initializer::Initializer>();
    std::string configPath("./config.ini");
    initialize->init(configPath);

    // use log
    sampleLog();

    try {
        printVersion(PROJECT_NAME);
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}