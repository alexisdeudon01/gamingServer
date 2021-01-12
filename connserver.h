#ifndef CONNSERVER_H
#define CONNSERVER_H
#include <Winsock2.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <string>
#include <QMainWindow>
#include <list>

#include "./ui_mainwindow.h"

#include <QMessageBox>
class ConnServer
{
public:

    ConnServer(Ui::MainWindow *ui);
    ~ConnServer();
    bool ConnectToServer(char* ip,char* port,char* username, char* password);
    std::string receiveMessage();
    void showConnError(std::string message);
    std::string getListGames();
    void sendMsg(char *msg);
    std::string findFreePlayers();
    std::list<std::string> decomposePlayer(std::string responseServer);
    std::string getUser();
private:
    Ui::MainWindow *ui;
    std::string user;
    SOCKET sock;
};

#endif // CONNSERVER_H
