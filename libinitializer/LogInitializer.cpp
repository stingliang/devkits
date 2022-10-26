/**
 * @project Devkits
 * @file LogInitializer.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/26 21:00:54
 */

#include "LogInitializer.h"

#include <boost/log/core/core.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/algorithm/string.hpp>
#include <exception>
#include <stdexcept>


using namespace dev::initializer;

namespace logging = boost::log;
namespace expr = boost::log::expressions;

BOOST_LOG_ATTRIBUTE_KEYWORD(component_id, "ComponentId", std::string)

void LogInitializer::initLog(boost::property_tree::ptree const& _pt, std::string const& _channel,
                             std::string const& _logPrefix) {
    std::string logPath = _pt.get<std::string>("log.log_path", "log");
    /// set log level
    unsigned logLevel = getLogLevel(_pt.get<std::string>("log.level", "info"));
    auto sink = initLogSink(_pt, logLevel, logPath, _logPrefix, _channel);

    setFileLogLevel((LogLevel)logLevel);

    /// set file format
    /// log-level|timestamp|[component_id] message
    sink->set_formatter(
            expr::stream
                    << boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity") << "|"
                    << boost::log::expressions::format_date_time<boost::posix_time::ptime>(
                            "TimeStamp", "%Y-%m-%d %H:%M:%S")
                    << "|" << expr::if_(expr::has_attr(component_id))[expr::stream << "[" << component_id << "]"]
                    << boost::log::expressions::smessage);
}

boost::shared_ptr<dev::initializer::LogInitializer::sink_t> LogInitializer::initLogSink(
        boost::property_tree::ptree const& pt, unsigned const& _logLevel, std::string const& _logPath,
        std::string const& _logPrefix, std::string const& channel)
{
    m_currentHourVec.push_back(
            (int)boost::posix_time::second_clock::local_time().time_of_day().hours());
    /// set file name
    std::string fileName = _logPath + "/" + _logPrefix + "_%Y%m%d%H%M.log";
    boost::shared_ptr<sink_t> sink(new sink_t());

    sink->locked_backend()->set_open_mode(std::ios::app);

    /// handler to solve log rotate
    sink->locked_backend()->set_time_based_rotation([this]{
        auto _index = m_currentHourVec.size() - 1;
        const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
        int hour = (int)now.time_of_day().hours();
        if (hour != m_currentHourVec[_index])
        {
            m_currentHourVec[_index] = hour;
            return true;
        }
        return false;
    });
    sink->locked_backend()->set_file_name_pattern(fileName);
    /// set rotation size MB
    uint64_t rotation_size = pt.get<uint64_t>("log.max_log_file_size", 200) * (1024 * 1024);
    sink->locked_backend()->set_rotation_size(rotation_size);
    /// set auto-flush according to log configuration
    bool need_flush = pt.get<bool>("log.flush", true);
    sink->locked_backend()->auto_flush(need_flush);

    struct LogExpHandler
    {
        void operator()(std::runtime_error const& e) const
        {
            std::cout << "std::runtime_error: " << e.what() << std::endl;
            throw;
        }
        void operator()(std::logic_error const& e) const
        {
            std::cout << "std::logic_error: " << e.what() << std::endl;
            throw;
        }
    };

    sink->set_filter(boost::log::expressions::attr<std::string>("Channel") == channel &&
                     boost::log::trivial::severity >= _logLevel);

    logging::core::get()->set_exception_handler(
            logging::make_exception_handler<std::runtime_error, std::logic_error>(LogExpHandler()));

    boost::log::core::get()->add_sink(sink);
    m_sinks.push_back(sink);
    bool enable_log = pt.get<bool>("log.enable", true);
    boost::log::core::get()->set_logging_enabled(enable_log);
    // add attributes
    boost::log::add_common_attributes();
    return sink;
}

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
    for (auto const& sink : m_sinks)
        stopLogging(sink);
    m_sinks.clear();
}

/// stop a single sink
void LogInitializer::stopLogging(boost::shared_ptr<sink_t> sink)
{
    if (!sink)
        return;
    // remove the sink from the core, so that no records are passed to it
    boost::log::core::get()->remove_sink(sink);
    // break the feeding loop
    sink->stop();
    // flush all log records that may have left buffered
    sink->flush();
    sink.reset();
}
