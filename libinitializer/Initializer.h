/**
 * @project Devkits
 * @file Initializer.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 00:17:24
 */

#ifndef DEVKITS_INITIALIZER_H
#define DEVKITS_INITIALIZER_H

#include <memory>

#include "InitializerInterface.h"
#include "LogInitializer.h"

namespace dev {
    namespace initializer {
        class Initializer: public InitializerInterface, public std::enable_shared_from_this<Initializer> {
        public:
            using Ptr = std::shared_ptr<Initializer>;

            Initializer() = default;
            ~Initializer() override;
            void init(std::string const& _path) override;

        private:
            LogInitializer::Ptr m_logInitializer = nullptr;
        };

    } // dev
} // initializer

#endif //DEVKITS_INITIALIZER_H
