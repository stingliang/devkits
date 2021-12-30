//
// Created by Liang on 2021/9/17.
//

#include <iostream>
#include <BuildInfo.h>

int main (int argc, const char* argv[]) {
    try {
        std::cout << "Hello, World!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}