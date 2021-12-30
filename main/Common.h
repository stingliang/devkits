//
// Created by liang on 2021/12/31.
//

#ifndef SAMPLE_COMMON_H
#define SAMPLE_COMMON_H

#include <iostream>

#include <boost/version.hpp>

#include "BuildInfo.h"

inline void printVersion()
{
    std::cout << "Sample Version     : " << SAMPLE_PROJECT_VERSION << std::endl;
    std::cout << "Build Time         : " << SAMPLE_BUILD_TIME << std::endl;
    std::cout << "Build Type         : " << SAMPLE_BUILD_PLATFORM << "/"
                                         << SAMPLE_BUILD_TYPE << std::endl;
    std::cout << "Git Branch         : " << SAMPLE_BUILD_BRANCH << std::endl;
    std::cout << "Git Commit         : " << SAMPLE_COMMIT_HASH << std::endl;
    std::cout << "Boost Version      : " << BOOST_LIB_VERSION << std::endl;
}

#endif //SAMPLE_COMMON_H
