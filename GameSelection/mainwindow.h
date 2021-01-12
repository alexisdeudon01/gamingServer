#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QVBoxLayout>
#include "connserver.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_manAutoButton_clicked();
private:
    Ui::MainWindow *ui;
    ConnServerGS *myConn;
    void decomposeGame(std::string responseServer);

};
#endif // MAINWINDOW_H
