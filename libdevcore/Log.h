/**
 * @project Devkits
 * @file Log.h
 * @author liangrui (liangrui5526@126.com)
 * @date 2021/9/29 14:30:57
 */

#ifndef DEV_UTILITY_LOGGER_H
#define DEV_UTILITY_LOGGER_H

#include "Common.h"

// boost include
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;

#define LOGGER(MODULE, SEVERITY) BOOST_LOG_TRIVIAL(SEVERITY) << "[" << (MODULE) << "] "

namespace dev {
    class log_initializer {
    public:
        struct log_config {

            // print log to consoles or not
            bool console_print = true;

            // log severity
            logging::trivial::severity_level severity = boost::log::trivial::info;

            // log path
            std::string log_path;

            // maximum size per log file
            size_t logfile_maxsize = 128 *1024 *1024;
        };

        // init log module with struct "log_config"
        static void init(const log_config&);

    private:
        static bool isInit() { return init_flag; }
        static bool init_flag;
    };
}

#endif //DEV_UTILITY_LOGGER_H
