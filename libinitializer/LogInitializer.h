/**
 * @project Devkits
 * @file LogInitializer.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/26 21:00:54
 */

#ifndef DEVKITS_LOGINITIALIZER_H
#define DEVKITS_LOGINITIALIZER_H

#include "libdevcore/Log.h"

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>

namespace devkits {
    namespace initializer {
        class LogInitializer {
        public:
            class Sink : public boost::log::sinks::text_file_backend {
            public:
                void consume(const boost::log::record_view& rec, const std::string& str) {
                    boost::log::sinks::text_file_backend::consume(rec, str);
                    auto severity =
                            rec.attribute_values()[boost::log::aux::default_attribute_names::severity()]
                                    .extract<boost::log::trivial::severity_level>();
                    if (severity.get_ptr() && severity.get() == boost::log::trivial::severity_level::fatal) {
                        // abort if encounter fatal, will generate coredump
                        // must make sure only use LOG(FATAL) when encounter the most serious problem
                        // forbid use LOG(FATAL) in the function that should exit normally
                        std::abort();
                    }
                }
            };
            using Ptr = std::shared_ptr<LogInitializer>;
            using sink_t = boost::log::sinks::asynchronous_sink<Sink>;
            virtual ~LogInitializer() { stopLogging(); }
            LogInitializer() = default;

            /**
             * @brief: set log for specified channel
             *
             * @param _pt: ptree that contains the log configuration
             * @param channel: channel name
             * @param logType: log prefix
             * @note ptree should contains following key-value pair:\n
             *          - log.log_path [string]\n
             *          - log.level [string] fatal/error/warning/info/debug/trace\n
             *          - log.max_log_file_size [unsigned int] unit is MB\n
             *          - log.flush [bool] 0/1 if flush log immediately\n
             *          - log.enable [bool] 0/1 open log or not\n
             */
            void initLog(boost::property_tree::ptree const& _pt,
                         std::string const& _channel = FileLogger, std::string const& _logPrefix = "log");

            void stopLogging();

            /**
             * @brief: get log level according to given string
             *
             * @param levelStr: the given string that should be transformed to boost log level
             * @return unsigned: the log level
             */
            static unsigned getLogLevel(std::string const& levelStr);

        private:

            boost::shared_ptr<sink_t> initLogSink(boost::property_tree::ptree const& _pt,
                                                  unsigned const& _logLevel, std::string const& _logPath,
                                                  std::string const& _logPrefix, std::string const& channel);

        private:
            static void stopLogging(boost::shared_ptr<sink_t> sink);
            std::vector<boost::shared_ptr<sink_t>> m_sinks;
            std::vector<int> m_currentHourVec;
        };
    }  // namespace initializer
}  // namespace devkits


#endif //DEVKITS_LOGINITIALIZER_H
