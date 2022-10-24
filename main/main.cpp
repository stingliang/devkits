#include "BuildInfo.h"
#define PROJECT_NAME "Devkits"
int main (int argc, const char* argv[]) {
    try {
        printVersion(PROJECT_NAME);
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}