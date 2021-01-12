

#include <QApplication>
#define WIN32_LEAN_AND_MEAN

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
   FreeConsole();
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2,2);
    if(WSAStartup(DllVersion, &wsaData)!=0)
        ExitProcess(EXIT_FAILURE);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
