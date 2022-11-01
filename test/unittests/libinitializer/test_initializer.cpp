/**
 * @project Devkits
 * @file test_innitializer.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 23:23:46
 */

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "libinitializer/Initializer.h"
#include "tools/Options.h"

#define TEST_LOG(LEVEL) LOG(LEVEL) << "[InitializerFixture]"

struct InitializerFixture {

    InitializerFixture() = default;
    ~InitializerFixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(s_initializer, InitializerFixture)

    BOOST_AUTO_TEST_CASE(c_log) {

        // initialize all components
        auto initialize = std::make_shared<devkits::initializer::Initializer>();
        std::string configPath(devkits::test::Options::get().testpath + "/config.ini");
        BOOST_REQUIRE(boost::filesystem::is_regular_file(configPath));
        initialize->init(configPath);

        TEST_LOG(TRACE) << "This is a trace log";
        TEST_LOG(DEBUG) << "This is a debug log";
        TEST_LOG(INFO) << "This is a info log";
        TEST_LOG(WARNING) << "This is a warning log";
        TEST_LOG(ERROR) << "This is a error log";
//    TEST_LOG(FATAL) << "This is a fatal log"; /**< It will cause coredump */
        TEST_LOG(INFO) << LOG_KV("Component", "example") << "This is a key-value log";
    }

BOOST_AUTO_TEST_SUITE_END()
