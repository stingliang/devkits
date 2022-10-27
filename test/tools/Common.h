/**
 * @project Devkits
 * @file Common.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 23:50:49
 */

#ifndef DEVKITS_COMMON_H
#define DEVKITS_COMMON_H


#include "Options.h"

#include <boost/filesystem.hpp>

#include <string>
#include <set>

namespace dev {
    namespace test {

        inline boost::filesystem::path getTestPath() {
            boost::filesystem::path(dev::test::Options::get().testpath);
        }

        inline std::vector<boost::filesystem::path> getFiles(
                boost::filesystem::path const& dirPath, std::set<std::string> const& extensionLists) {
            std::vector<boost::filesystem::path> files;
            for (std::string const& extItem : extensionLists) {
                using fsIterator = boost::filesystem::directory_iterator;
                for (fsIterator it(dirPath); it != fsIterator(); it++)
                {
                    if (boost::filesystem::is_regular_file(it->path()) && it->path().extension() == extItem)
                        files.push_back(it->path());
                }
            }
            return files;
        }

    }  // namespace test
}  // namespace dev

#endif //DEVKITS_COMMON_H
