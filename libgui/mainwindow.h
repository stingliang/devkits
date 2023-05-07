/**
 * @project Devkits
 * @file mainwindow.h
 * @author liangrui (liangrui5526@126.com)
 * @date 2022/11/29 23:56:17
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    using Ptr = std::shared_ptr<MainWindow>;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
