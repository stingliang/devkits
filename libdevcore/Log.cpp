//
// Created by stingliang on 2021/9/29 14:30.
//

#include "Log.h"

bool log_initializer::init_flag(false);

void log_initializer::init(const log_config &config) {
    if (isInit()) { return; }
    logging::core::get()->set_filter(logging::trivial::severity >= config.severity);
    // set log format
    auto fmt = (
            expr::stream
                    << "["
                    << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                    << "][" << logging::trivial::severity
                    << "]" << expr::smessage
    );
    if (config.console_print) {
        boost::log::add_console_log(
                std::cout,
                logging::keywords::format = fmt
        );
    }
    if (!config.log_path.empty()) {
        boost::posix_time::ptime datetime = boost::posix_time::second_clock::local_time();
        boost::posix_time::ptime pt(datetime.date(), datetime.time_of_day());
        std::string file_name = config.log_path + "/" + to_iso_string(pt) + ".log";
        logging::add_file_log(
                keywords::file_name = file_name,
                keywords::rotation_size = config.logfile_maxsize,
                keywords::format = fmt
        );
    }
    logging::add_common_attributes();
    init_flag = true;

} // devkits end