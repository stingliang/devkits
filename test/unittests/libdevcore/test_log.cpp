//
// Created by liang on 2021/11/15.
//

#include <libdevcore/Log.h>

#include <boost/test/unit_test.hpp>

#define SAMPLE_LOG(SEVERITY) LOGGER("Sample", SEVERITY)

struct SampleFixture {

    SampleFixture() {
        // config log
        auto config = log_initializer::log_config();
        config.severity = boost::log::trivial::trace;
        log_initializer::init(config);
    };
    ~SampleFixture() = default;

    std::string samp_data;
};

BOOST_FIXTURE_TEST_SUITE(s_devcore, SampleFixture)  /* NOLINT */

    BOOST_AUTO_TEST_CASE(c_log) {  /* NOLINT */
        SAMPLE_LOG(info) << "This is a sample log";
        BOOST_CHECK(true);
    }

BOOST_AUTO_TEST_SUITE_END()  /* NOLINT */
