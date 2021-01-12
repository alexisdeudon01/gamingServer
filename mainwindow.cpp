#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "mainwindow.h"
#include "connserver.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



#include <Winsock2.h>
#include <Winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <ws2tcpip.h>
#include <stdio.h>
#include <String.h>
#include "gameboard.h"
#include <QListWidget>
#include <thread>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->parent=parent;
    ui->setupUi(this);
    this->setWindowTitle("Chess gaming");
    ui->label_3->setVisible(false);


    this->myConn=new ConnServer(ui);
setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //Username
    QString textEditText = ui->lineEdit->text();
    QByteArray ba = textEditText.toLocal8Bit();
    const char *username = ba.data();
    //Password
    QString textEditText2 = ui->lineEdit_2->text();
    QByteArray ba2 = textEditText2.toLocal8Bit();
    const char *password = ba2.data();
    bool result=this->myConn->ConnectToServer("192.168.178.61","2401",(char*)username,(char*)password);

    if(result==true){

        GameBoard *game=new GameBoard(this,this->myConn);
        std::list<std::string> results=this->myConn->decomposePlayer(this->myConn->findFreePlayers());
        game->show();
        game->createWindowPlayer();
        game->ListPlayerGUI(results);
        this->hide();


    }

}
