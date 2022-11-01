/**
 * @project Devkits
 * @file Options.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/10/27 23:46:29
 */

#ifndef DEVKITS_OPTIONS_H
#define DEVKITS_OPTIONS_H

#include <string>
#include <vector>

namespace devkits {
    namespace test {
        class Options {
        public:
            std::string testpath;  ///< Custom test folder path

            /// Test selection
            /// @{
            bool all = false;  ///< Running every test, including time consuming ones.
            /// @}

            /// The first time used, options are parsed with argc, argv
            /// static Options const& get(int argc = 0, const char** argv = 0);
            static Options const& get();
            static Options const& get(int argc, char** argv);

        private:
            // Options(int argc = 0, const char** argv = 0);
            Options(int argc = 0, char** argv = 0);
            Options(Options const&) = delete;
        };

    }  // namespace test
}  // namespace devkits


#endif //DEVKITS_OPTIONS_H
