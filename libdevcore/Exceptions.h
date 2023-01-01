/**
 * @project Devkits
 * @file Exceptions.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 00:53:57
 */

#ifndef DEVKITS_EXCEPTIONS_H
#define DEVKITS_EXCEPTIONS_H

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/info_tuple.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp>
#include <exception>
#include <string>

namespace devkits {
    /**
     * @brief : Base class for all exceptions
     */
    struct Exception : virtual std::exception, virtual boost::exception {
        explicit Exception(std::string _message = std::string()) : m_message(std::move(_message)) {}
        const char* what() const noexcept override {
            return m_message.empty() ? std::exception::what() : m_message.c_str();
        }

    private:
        std::string m_message;
    };

    using err_no = boost::error_info<struct tag_err_no, int>;
    using err_str = boost::error_info<struct tag_err_str, std::string>;

/// construct a new exception class overriding Exception
#define DEV_SIMPLE_EXCEPTION(X)  \
    struct X : virtual Exception \
    {                            \
    }

    /// Exceptions
    DEV_SIMPLE_EXCEPTION(InvalidConfiguration);
    DEV_SIMPLE_EXCEPTION(InvalidPort);
    DEV_SIMPLE_EXCEPTION(InvalidSupportedVersion);
    DEV_SIMPLE_EXCEPTION(InvalidAddress);

    /**
     * @brief : error information to be added to exceptions
     */
    using errinfo_path = boost::error_info<struct tag_path, std::string>;
}  // namespace devkits

#endif //DEVKITS_EXCEPTIONS_H
