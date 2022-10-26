/**
 * @project Devkits
 * @file Log.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/26 20:53:58
 */

#ifndef DEVKITS_LOG_H
#define DEVKITS_LOG_H

#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/trivial.hpp>

// BCOS log format
#define LOG_BADGE(_NAME) "[" << (_NAME) << "]"
#define LOG_TYPE(_TYPE) (_TYPE) << "|"
#define LOG_DESC(_DESCRIPTION) (_DESCRIPTION)
#define LOG_KV(_K, _V) "[" << (_K) << "=" << (_V) << "]"

namespace dev {
    extern std::string const FileLogger;
    // the file logger
    extern boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level,
            std::string>
            FileLoggerHandler;

    enum LogLevel {
        FATAL = boost::log::trivial::fatal,
        ERROR = boost::log::trivial::error,
        WARNING = boost::log::trivial::warning,
        INFO = boost::log::trivial::info,
        DEBUG = boost::log::trivial::debug,
        TRACE = boost::log::trivial::trace
    };

    extern LogLevel c_fileLogLevel;
    extern LogLevel c_statLogLevel;

    void setFileLogLevel(LogLevel const& _level);
    void setStatLogLevel(LogLevel const& _level);

#define LOG(level)                                   \
    if (dev::LogLevel::level >= dev::c_fileLogLevel) \
    BOOST_LOG_SEV(dev::FileLoggerHandler,            \
        (boost::log::v2_mt_posix::trivial::severity_level)(dev::LogLevel::level))

}  // namespace dev


#endif //DEVKITS_LOG_H
