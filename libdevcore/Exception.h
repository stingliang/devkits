//
// Created by liang on 2021/11/21.
//

#ifndef STS_DATA_ACQUISITION_EXCEPTION_H
#define STS_DATA_ACQUISITION_EXCEPTION_H

#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>

#include <exception>

struct Exception : virtual std::exception, virtual boost::exception
{
    Exception(std::string _message = std::string()) : m_message(std::move(_message)) {}
    const char* what() const noexcept override
    {
        return m_message.empty() ? std::exception::what() : m_message.c_str();
    }

private:
    std::string m_message;
};

#endif //STS_DATA_ACQUISITION_EXCEPTION_H
