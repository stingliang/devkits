/**
 * @project Devkits
 * @file gui.h
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/11/29 01:32:08
 */

#ifndef DEVKITS_GUI_H
#define DEVKITS_GUI_H

#include "mainwindow.h"

#include <QApplication>
#include <utility>

class MainGui {
public:

    using Ptr = std::shared_ptr<MainGui>;

    template<class T>
    static Ptr create(int argc = 0, char **argv = nullptr) {
        static_assert(std::is_base_of_v<MainWindow, T>, "The template type is not a derived class of MainWindow");
        QApplication a(argc, argv);
        auto window = std::make_shared<T>();
        if (window) {
            MainGui::Ptr object(new MainGui(window));
            return object;
        } else {
            return nullptr;
        }
    }

    /**
     * Start application
     * @return
     */
    int exec();

    MainGui() = delete;

private:
    explicit MainGui(MainWindow::Ptr window): m_window(std::move(window)) {};

    MainWindow::Ptr m_window;
};

#endif //DEVKITS_GUI_H
