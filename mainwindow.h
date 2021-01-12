#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connserver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void ListPlayerGUI(std::list<std::string> listPlayer);

    ~MainWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ConnServer *myConn;
    QWidget* parent;

};
#endif // MAINWINDOW_H
