/**
 * @project Devkits
 * @file mainwindow.cpp
 * @author liangrui (liangrui5526@126.com)
 * @date 2022/11/29 23:56:17
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

