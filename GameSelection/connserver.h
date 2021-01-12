#ifndef CONNSERVER_H
#define CONNSERVER_H
#include <Winsock2.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <string>
#include <QMainWindow>


#include "./ui_mainwindow.h"

#include <QMessageBox>
class ConnServerGS
{
public:

    ConnServerGS(Ui::MainWindow *ui);
    bool ConnectToServer(char* ip,char* port);
    std::string receiveMessage();
    void showConnError(std::string message);
    std::string getListGames();
    void sendMsg(char *msg);
    std::string calculateHashFile(std::string path);
    std::string downloadHTTP(std::string url);
    bool execFile(std::string filePath);

private:
    Ui::MainWindow *ui;

    SOCKET sock2;
};

#endif // CONNSERVER_H
