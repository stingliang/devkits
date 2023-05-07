/**
 * @project Devkits
 * @file gui_demo.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/11/29 00:03:37
 */

#include "libgui/gui.h"

#include <memory>

class AppWindowDemo: public MainWindow {
    // This is an empty class whose function is to create a blank window
};

int main(int argc, char *argv[]) {
    auto demoWindow = MainGui::create<AppWindowDemo>(argc, argv);
    return demoWindow->exec();
}
