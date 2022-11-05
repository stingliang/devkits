/**
 * @project Devkits
 * @file LogInitializer.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/26 21:00:54
 */

#include "LogInitializer.h"
#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/algorithm/string.hpp>
#include <exception>
#include <stdexcept>


using namespace devkits::initializer;

/**
 * @brief: set log for specified channel
 *
 * @param pt: ptree that contains the log configuration
 * @param channel: channel name
 * @param logType: log prefix
 */
void LogInitializer::initLog(boost::property_tree::ptree const& _pt, std::string const& _channel,
                             std::string const& _logPrefix) {
    // get log level
    unsigned logLevel = getLogLevel(_pt.get<std::string>("log.level", "info"));
    bool consoleLog = _pt.get<bool>("log.enable_console_output", true);
    if (consoleLog) {
        boost::shared_ptr<console_sink_t> sink = initConsoleLogSink(_pt, logLevel, _channel);
        setLogFormatter(sink);
    } else {
        std::string logPath = _pt.get<std::string>("log.log_path", "log");
        boost::shared_ptr<sink_t> sink = initLogSink(_pt, logLevel, logPath, _logPrefix, _channel);
        setLogFormatter(sink);
    }
    setFileLogLevel((LogLevel)logLevel);
}

boost::shared_ptr<console_sink_t> LogInitializer::initConsoleLogSink(
        boost::property_tree::ptree const& _pt, unsigned const& _logLevel, std::string const& channel) {
    boost::log::add_common_attributes();
    boost::shared_ptr<console_sink_t> consoleSink(new console_sink_t());
    consoleSink->locked_backend()->add_stream(
            boost::shared_ptr<std::ostream>(&std::cout, boost::null_deleter()));

    bool need_flush = _pt.get<bool>("log.flush", true);
    consoleSink->locked_backend()->auto_flush(need_flush);
    consoleSink->set_filter(boost::log::expressions::attr<std::string>("Channel") == channel &&
                            boost::log::trivial::severity >= _logLevel);
    boost::log::core::get()->add_sink(consoleSink);
    m_consoleSinks.push_back(consoleSink);
    bool enable_log = _pt.get<bool>("log.enable", true);
    boost::log::core::get()->set_logging_enabled(enable_log);
    return consoleSink;
}

boost::shared_ptr<sink_t> LogInitializer::initLogSink(boost::property_tree::ptree const& pt,
                                                      unsigned const& _logLevel, std::string const& _logPath,
                                                      std::string const& _logPrefix,
                                                      std::string const& channel) {
    m_currentHourVec.push_back(
            (int)boost::posix_time::second_clock::local_time().time_of_day().hours());
    /// set file name
    std::string fileName = _logPath + "/" + _logPrefix + "_%Y%m%d%H%M.log";
    boost::shared_ptr<sink_t> sink(new sink_t());

    sink->locked_backend()->set_open_mode(std::ios::app);
    sink->locked_backend()->set_time_based_rotation([this]()->bool{
        const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
        int hour = (int)now.time_of_day().hours();
        if (hour != m_currentHourVec[m_currentHourVec.size() - 1]) {
            m_currentHourVec[m_currentHourVec.size() - 1] = hour;
            return true;
        }
        return false;
    });
    sink->locked_backend()->set_file_name_pattern(fileName);
    /// set rotation size MB
    uint64_t rotation_size = pt.get<uint64_t>("log.max_log_file_size", 200) * 1024 * 1024;
    sink->locked_backend()->set_rotation_size(rotation_size);
    /// set auto-flush according to log configuration
    bool need_flush = pt.get<bool>("log.flush", true);
    sink->locked_backend()->auto_flush(need_flush);

    struct LogExpHandler {
        void operator()(std::runtime_error const& e) const {
            std::cout << "std::runtime_error: " << e.what() << std::endl;
            throw;
        }
        void operator()(std::logic_error const& e) const {
            std::cout << "std::logic_error: " << e.what() << std::endl;
            throw;
        }
    };

    sink->set_filter(boost::log::expressions::attr<std::string>("Channel") == channel &&
                     boost::log::trivial::severity >= _logLevel);

    boost::log::core::get()->set_exception_handler(
            boost::log::make_exception_handler<std::runtime_error, std::logic_error>(LogExpHandler()));

    boost::log::core::get()->add_sink(sink);
    m_sinks.push_back(sink);
    bool enable_log = pt.get<bool>("log.enable", true);
    boost::log::core::get()->set_logging_enabled(enable_log);
    // add attributes
    boost::log::add_common_attributes();
    return sink;
}

/**
 * @brief: get log level according to given string
 *
 * @param levelStr: the given string that should be transformed to boost log level
 * @return unsigned: the log level
 */
unsigned LogInitializer::getLogLevel(std::string const& levelStr)
{
    if (boost::iequals(levelStr, "trace"))
        return boost::log::trivial::severity_level::trace;
    if (boost::iequals(levelStr, "debug"))
        return boost::log::trivial::severity_level::debug;
    if (boost::iequals(levelStr, "warning"))
        return boost::log::trivial::severity_level::warning;
    if (boost::iequals(levelStr, "error"))
        return boost::log::trivial::severity_level::error;
    if (boost::iequals(levelStr, "fatal"))
        return boost::log::trivial::severity_level::fatal;
    /// default log level is info
    return boost::log::trivial::severity_level::info;
}

/// stop and remove all sinks after the program exit
void LogInitializer::stopLogging()
{
    for (auto const& sink : m_sinks) {
        stopLogging(sink);
    }
    m_sinks.clear();

    for (auto const& sink : m_consoleSinks) {
        stopLogging(sink);
    }
    m_consoleSinks.clear();
}
