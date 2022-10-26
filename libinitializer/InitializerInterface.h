/**
 * @project Devkits
 * @file InitializerInterface.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 00:39:47
 */

#ifndef DEVKITS_INITIALIZERINTERFACE_H
#define DEVKITS_INITIALIZERINTERFACE_H

#include <string>

namespace dev
{
    namespace initializer
    {
        class InitializerInterface
        {
        public:
            InitializerInterface() = default;
            virtual ~InitializerInterface() = default;

            virtual void init(std::string const& _path) = 0;
        };
    }  // namespace initializer
}  // namespace dev

#endif //DEVKITS_INITIALIZERINTERFACE_H
