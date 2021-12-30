//
// Created by Liang on 2021/9/17.
//

#define BOOST_TEST_MAIN
// boost include
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>

#include "libnetwork/common.h"
#include "libnetwork/sender.h"
#include <test/receiver.h>

#define TEST_LOG(SEVERITY) LOGGER("Test", SEVERITY)
#define POINT_NUMBER 24000
#define LIDAR_EXIST 0

using namespace std::chrono_literals;
using namespace boost::assign;

struct Fixture {
    Fixture () {
        // init log
        auto config = log_initializer::log_config();
        config.log_path = "./log";
        config.severity = boost::log::trivial::debug;
        log_initializer::init(config);

        // init test data
        empty_lidar_data.resize(sizeof(LidarPoint) * 24000);
        sn_vector += "0TXXXXXXXXXXXX0", "0TXXXXXXXXXXXX1", "0TXXXXXXXXXXXX2";
        host_vector += std::make_pair<std::string, int>("127.0.0.1", 6687),
                       std::make_pair<std::string, int>("127.0.0.1", 6688),
                       std::make_pair<std::string, int>("127.0.0.1", 6689);

        TEST_LOG(info) << "Constract fixture.";
        // sleep duration
        sleep_duration = 15;
    }
    ~Fixture () {
        if (fixture_lw && fixture_lw->isInitialized()) { fixture_lw->deInitialize(); }
        thread_g.interrupt_all();
        TEST_LOG(info) << "Destroyed fixture.";
    }

    void connect2lidar() {
        fixture_lw.reset(LivoxsdkWrapper::getInstance());
        fixture_lw->initialize();
    };

    bool receive_ornot = true;
    size_t sleep_duration;
    std::string empty_lidar_data;
    LivoxsdkWrapper::Ptr fixture_lw = nullptr;
    std::vector<std::string> sn_vector;
    std::vector<std::pair<std::string, int>> host_vector;
    std::vector<std::shared_ptr<Receiver>> receiver_vector;
    boost::thread_group thread_g;
};

BOOST_FIXTURE_TEST_SUITE (s_main, Fixture)  /* NOLINT */

BOOST_AUTO_TEST_CASE(c_send_and_receive) {  /* NOLINT */
    receive_ornot = false;
    // init receiver
    thread_g.create_thread([&](){
        for (const auto& host: host_vector) {
            receiver_vector.push_back(std::make_shared<Receiver>(host.second));
        }
    });
    auto senders = std::make_shared<std::vector<Sender::Ptr>>();
    for (const auto& host: host_vector) {
        auto sender = std::make_shared<Sender>();
        sender->init(host.first, host.second, 100);
        sender->start();
        senders->push_back(sender);
    }
    // log printer
    thread_g.create_thread([&](){
        float timer(0);
        while (senders) {
            timer += 1.0;
            auto data_send_amount = Sender::sm_send_data_amount.load();
            std::stringstream ss;
            ss << "[Running " << timer << "s] "
               << "Send data amount: " << data_send_amount << " MB"
               << ", Current global speed: " << data_send_amount / timer << " MB/s.";
            TEST_LOG(info) << ss.str();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });
#if LIDAR_EXIST
    // init lidar
    connect2lidar();
    // regist handler
    fixture_lw->registerPointsHandler([](
            std::string &lidarSN, std::size_t nPoints, const LidarPoint *points, uint64_t timestamp, void *pUserData
    ){
        // send point cloud
        auto* senders = static_cast<std::vector<Sender::Ptr>*>(pUserData);
        // processer factory
        auto processer_ptr = std::make_shared<Processor>(lidarSN);
        processer_ptr->inputPointCloudData(nPoints, points);
        for (const auto& sender: *senders) {
            sender->push(processer_ptr);
        }
    }, senders.get());
#else
    thread_g.create_thread([&](){
        while (senders) {
            auto processer_ptr = std::make_shared<Processor>(sn_vector.at(0));
            processer_ptr->inputPointCloudData(POINT_NUMBER, (LidarPoint*)empty_lidar_data.data());
            for (const auto& sender: *senders) {
                sender->push(processer_ptr);
            }
            std::this_thread::sleep_for(100ms);
        }
    });
#endif
    std::this_thread::sleep_for(std::chrono::seconds(sleep_duration));
}

BOOST_AUTO_TEST_CASE(c_receive) {  /* NOLINT */
    if (receive_ornot) {
        // init receiver
        thread_g.create_thread([&](){
            for (const auto& host: host_vector) {
                receiver_vector.push_back(std::make_shared<Receiver>(host.second));
            }
        });
        std::this_thread::sleep_for(std::chrono::seconds(sleep_duration));
    }
}

BOOST_AUTO_TEST_SUITE_END()  /* NOLINT */