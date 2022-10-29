/**
 * @project Devkits
 * @file test_devcore.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 23:20:39
 */

#define TEST_LOG(LEVEL) LOG(LEVEL) << "[DevcoreFixture]"

#include <boost/test/unit_test.hpp>

struct DevcoreFixture {

    DevcoreFixture() = default;
    ~DevcoreFixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(s_devcore, DevcoreFixture)

    BOOST_AUTO_TEST_CASE(c_threadPool) {}

BOOST_AUTO_TEST_SUITE_END()
