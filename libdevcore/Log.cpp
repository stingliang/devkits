/**
 * @project Devkits
 * @file Log.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/26 20:53:58
 */

#include "Log.h"

#include <boost/log/core.hpp>

namespace dev {
    std::string const FileLogger = "FileLogger";
    boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level, std::string>
            FileLoggerHandler(boost::log::keywords::channel = FileLogger);

    std::string const StatFileLogger = "StatFileLogger";
    boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level, std::string>
            StatFileLoggerHandler(boost::log::keywords::channel = StatFileLogger);

    LogLevel c_fileLogLevel = LogLevel::TRACE;

    void setFileLogLevel(LogLevel const& _level) {
        c_fileLogLevel = _level;
    }
}  // namespace dev
