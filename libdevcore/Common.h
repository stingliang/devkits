//
// Created by liang on 2021/11/15.
//

#ifndef STS_DATA_ACQUISITION_COMMON_H
#define STS_DATA_ACQUISITION_COMMON_H

// std include
#include <string>
#include <memory>
#include <array>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>

#define COUT(X) std::cout << X << std::endl;

/// copy std::string from shmem and no need to consider string size,
/// due to string in shmem and string in process own different allocator,
/// this function requires a template param.
/// \tparam T
/// \param data_in_process
/// \param data_in_shmem
template<class T>
void copyStringFromShmem(std::string& data_in_process, T& data_in_shmem) {
    std::string _data(data_in_shmem.size(), '0');
    memcpy((void*)(_data.data()), data_in_shmem.data(), _data.size());
    _data.swap(data_in_process);
}

/// /// copy std::string to shmem and no need to consider string size,
///// due to string in shmem and string in process own different allocator,
///// this function requires a template param.
/// \tparam T
/// \param data_in_process
/// \param data_in_shmem
template<class T>
void copyStringToShmem(std::string& data_in_process, T& data_in_shmem) {
    data_in_shmem.resize(data_in_process.size());
    memcpy((void*)(data_in_shmem.data()), data_in_process.data(), data_in_shmem.size());
}

#endif //STS_DATA_ACQUISITION_COMMON_H
