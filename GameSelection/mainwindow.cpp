#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <QPushButton>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->myConn=new ConnServerGS(ui);
    this->myConn->ConnectToServer("127.0.0.1","2401");
    string listGame=this->myConn->getListGames();
    decomposeGame(listGame);

}
void MainWindow::on_manAutoButton_clicked(){
    cout<<"You have clicked"<<endl;
    this->myConn->execFile("C:\\Qt\\6.0.0\\mingw81_64\\bin\\ChessProject.exe");
}
void MainWindow::decomposeGame(string responseServer){
    std::string delimiter = ",";

    size_t pos = 0;
    std::string token;
    QPushButton *btn;
    while ((pos = responseServer.find(delimiter)) != std::string::npos) {

        token = responseServer.substr(0, pos);
        token = token.substr(0, token.find("=", 0));
        std::cout << token << std::endl;
        responseServer.erase(0, pos + delimiter.length());
        btn=new QPushButton(token.c_str(),this);
    }
    connect(btn, SIGNAL(clicked()), this, SLOT(on_manAutoButton_clicked()));
    responseServer = responseServer.substr(0, responseServer.find("=", 0));
    std::cout <<  responseServer<< std::endl;

}
MainWindow::~MainWindow()
{
    delete ui;
}

