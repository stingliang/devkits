/**
 * @project Devkits
 * @file Options.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 23:46:29
 */

#include "Options.h"
#include <boost/program_options.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

namespace dev {
    namespace test {
        Options::Options(int argc, char** argv) {
            namespace po = boost::program_options;

            po::options_description test_options("test of devkits:");

            test_options.add_options()("testpath,t", boost::program_options::value<std::string>(),
                                       " set test path")("help,h", "help of test_devkits");

            po::variables_map vm;
            try {
                po::store(boost::program_options::parse_command_line(argc, argv, test_options), vm);
            } catch (...) {
                std::cout << "invalid input" << std::endl;
            }
            if (vm.count("help") || vm.count("h")) {
                std::cout << test_options << std::endl;
                exit(0);
            }
            else if (vm.count("--all")) { all = true; }
            else if (vm.count("testpath") || vm.count("t")) { testpath = vm["testpath"].as<std::string>(); }
        }

        Options const& Options::get(int argc, char** argv) {
            static Options instance(argc, argv);
            return instance;
        }

        Options const& Options::get() {
            return get(framework::master_test_suite().argc, framework::master_test_suite().argv);
        }
    }  // namespace test
}  // namespace dev
