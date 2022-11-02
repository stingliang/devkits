/**
 * @project Devkits
 * @file libdevcore_demo.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/11/2 23:56:17
 */

#include "libdevcore/Log.h"

void log() {
    LOG(TRACE) << "This is a trace log";
    LOG(DEBUG) << "This is a debug log";
    LOG(INFO) << "This is a info log";
    LOG(WARNING) << "This is a warning log";
    LOG(ERROR) << "This is a error log";
    LOG(FATAL) << "This is a fatal log";
    LOG(INFO) << LOG_BADGE("UnitTest") << "This is a log with badge";
    LOG(INFO) << LOG_TYPE("Test") << "This is a log with type info";
    LOG(INFO) << LOG_DESC("Unittest log describe");
    LOG(INFO) << LOG_KV("Component", "example") << "This is a key-value log";
}

int main() {

    log();

    return EXIT_SUCCESS;
}