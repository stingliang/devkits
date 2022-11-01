/**
 * @project Devkits
 * @file Log.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/26 20:53:58
 */

#include "Log.h"

#include <boost/log/core.hpp>

namespace devkits {
    std::string const FileLogger = "FileLogger";
    boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level, std::string>
            FileLoggerHandler(boost::log::keywords::channel = FileLogger);

    LogLevel c_fileLogLevel = LogLevel::TRACE;

    void setFileLogLevel(LogLevel const& _level) {
        c_fileLogLevel = _level;
    }
}  // namespace devkits
