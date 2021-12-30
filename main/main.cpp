//
// Created by Liang on 2021/9/17.
//

#include "Common.h"

int main (int argc, const char* argv[]) {
    try {
        printVersion();
        return EXIT_FAILURE;
    }
    catch (std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}