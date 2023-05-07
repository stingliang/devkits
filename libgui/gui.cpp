/**
 * @project Devkits
 * @file gui.cpp
 * @author liangrui (liangrui5526@126.com) 
 * @date 2022/11/29 01:32:20
 */

#include "gui.h"

#include <QApplication>

int MainGui::exec() {
    m_window->show();
    return QApplication::exec();
}
