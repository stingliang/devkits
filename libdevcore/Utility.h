/**
 * @project Devkits
 * @file Utility.h
 * @author liangrui (liangrui5526@126.com)
 * @date 2021/9/29 14:58:45
 */

#ifndef DEV_UTILITY_LIBRARY_UTILITY_H
#define DEV_UTILITY_LIBRARY_UTILITY_H

#include <sstream>
#include <vector>
#include <string>
#include <mutex>
#include <map>
#include <set>

///
/// \tparam T1
/// \tparam T2
/// \param std::map
/// \return std::stringstream
/// \brief print stl map
template<typename T1, typename T2>
std::stringstream printStl(std::map<T1,T2>& m) {
    std::stringstream ss;
    for(auto const& elem : m) {
        ss << "[" << elem.first << ":" << elem.second << "]";
    }
    return ss;
}

///
/// \tparam T
/// \param stl/boost container
/// \return std::stringstream
/// \brief print stl set
template<typename T>
std::stringstream printStl(T& s) {
    std::stringstream ss;
    for(auto const& elem : s) {
        ss << "[" << elem << "]";
    }
    return ss;
}

// string: bin->hex
std::string binToHex(const std::string &strBin, bool bIsUpper = false);

// string: bin->hex
std::string hexToBin(const std::string &strHex);

#endif //DEV_UTILITY_LIBRARY_UTILITY_H
