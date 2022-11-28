/**
 * @project Devkits
 * @file Initializer.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 00:17:24
 */

#include "libdevcore/Exceptions.h"
#include "Initializer.h"
#include "Common.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace devkits;
using namespace initializer;

Initializer::~Initializer() {
    // components should be stopped here
    // ...
}

void Initializer::init(const std::string &_path) {
    try {
        boost::property_tree::ptree pt;
        if (boost::filesystem::path(_path).extension() == ".ini") {
            boost::property_tree::read_ini(_path, pt);
        } else if (boost::filesystem::path(_path).extension() == ".json") {
            boost::property_tree::read_json(_path, pt);
        } else {
            BOOST_THROW_EXCEPTION(std::runtime_error("Unsupported config file format"));
        }


        /// init log
        m_logInitializer = std::make_shared<LogInitializer>();
        m_logInitializer->initLog(pt);

    } catch (std::exception& e) {
        INITIALIZER_LOG(ERROR) << LOG_BADGE("Initializer") << LOG_DESC("Init failed")
                               << LOG_KV("ERROR", boost::diagnostic_information(e));
        ERROR_OUTPUT << LOG_BADGE("Initializer") << LOG_DESC("Init failed")
                     << LOG_KV("ERROR", boost::diagnostic_information(e)) << std::endl;
        BOOST_THROW_EXCEPTION(e);
    }
}
