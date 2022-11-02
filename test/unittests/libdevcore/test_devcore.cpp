/**
 * @project Devkits
 * @file test_devcore.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 23:20:39
 */

#define TEST_LOG(LEVEL) LOG(LEVEL) << "[DevcoreFixture]"

#include <boost/test/unit_test.hpp>
#include <boost/atomic.hpp>

#include <chrono>

#include "libdevcore/Log.h"
#include "libdevcore/ThreadPool.h"

using namespace std::chrono_literals;

struct DevcoreFixture {

    DevcoreFixture() = default;
    ~DevcoreFixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(s_devcore, DevcoreFixture)

    BOOST_AUTO_TEST_CASE(c_threadPool) {
        size_t test_thread_number = boost::thread::hardware_concurrency();
        size_t test_pool_size = test_thread_number / 2;
        devkits::ThreadPool pool(test_pool_size);
        std::vector<std::future<int>> results;

        boost::atomic_int thread_counter(0), completed_counter(0);
        for(size_t i = 0; i < test_thread_number; ++i) {
            results.emplace_back(
                pool.enqueue([i, &thread_counter, &completed_counter] {
                    thread_counter++;
                    std::this_thread::sleep_for(std::chrono::milliseconds(i * 100));
                    thread_counter--;
                    completed_counter++;
                    return int(i);
                })
            );
        }

        // sleep 500ms to wait counter's increment
        std::this_thread::sleep_for(50ms);

        // there are 4 threads running parallel at this moment
        BOOST_CHECK_EQUAL(thread_counter.load(), test_pool_size);

        // the results vector was fulled by the future objects
        BOOST_CHECK_EQUAL(results.size(), test_thread_number);

        // check threads running results
        for (size_t i = 0; i < test_thread_number; ++i) {
            BOOST_CHECK_EQUAL(results.at(i).get(), i);
        }

        // all of 10 threads were completed
        BOOST_CHECK_EQUAL(completed_counter.load(), test_thread_number);

    }

BOOST_AUTO_TEST_SUITE_END()
