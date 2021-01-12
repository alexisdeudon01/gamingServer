#include "connserver.h"



#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "./ui_mainwindow.h"
#include <QMessageBox>
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <ws2tcpip.h>
#include <stdio.h>
#include <String.h>
#include <string>
#include <QMainWindow>
#include <QScrollBar>
#include <QListWidget>
#include <QHBoxLayout>
using namespace std;



ConnServerGS::ConnServerGS(Ui::MainWindow *ui)
{
this->ui=ui;

}
string ConnServerGS::getListGames(){
    char* listGameCmd="GETLISTGAME\n";
    sendMsg(listGameCmd);
    char *szBuffer=new char[1024];
    string szTemp=receiveMessage();

    return szTemp;
}
string ConnServerGS::receiveMessage()
{
    char buffer[4096];
    std::string myString;
    int nDataLength;
    nDataLength = recv(this->sock2, buffer, sizeof(buffer), 0);
    myString.append(buffer, nDataLength);
    return myString ;
}

void ConnServerGS::sendMsg(char* msg)
{
  if(! send(this->sock2,msg,strlen(msg),0)){
    showConnError("Cannot send  data");
  }
}

void ConnServerGS::showConnError(string message){
    QMessageBox messageBox;
    messageBox.critical(0,"Error",message.c_str());
    messageBox.setFixedSize(500,200);
}

string ConnServerGS::calculateHashFile(string path){
    //Calculate the hash of a file
}
string ConnServerGS::downloadHTTP(string url){
    //Download file through http protocol and save it into specific folder
}
bool ConnServerGS::execFile(string filePath){
    //execute specific file
     ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
     return true;
}
bool ConnServerGS::ConnectToServer(char* ip,char* port){
 //Initialise winsock
 WSAData wsaData;
 WORD DllVersion = MAKEWORD(2,2);

 if(WSAStartup(DllVersion, &wsaData)!=0)
     showConnError("Can't initialize winsock");
 //Create a socket
 this->sock2=socket(AF_INET,SOCK_STREAM,0);
 if (this->sock2 == INVALID_SOCKET)
         wprintf(L"socket function failed with error = %d\n", WSAGetLastError() );

 HOSTENT *host=gethostbyname("127.0.0.1");
 DWORD dwError;
 if (host == NULL) {
     dwError = WSAGetLastError();
     if (dwError != 0) {
         if (dwError == WSAHOST_NOT_FOUND) {
             printf("Host not found\n");
             return 1;
         } else if (dwError == WSANO_DATA) {
             printf("No data record found\n");
             return 1;
         } else {
             printf("Function failed with error: %ld\n", dwError);
             return 1;
         }
     }
 }
 //Bind the socket
 sockaddr_in hint;
 ZeroMemory(&hint, sizeof(hint));
 hint.sin_family=AF_INET;
 hint.sin_port=htons(2401);
 memcpy(&hint.sin_addr.S_un.S_addr,host->h_addr_list[0], sizeof(hint.sin_addr.S_un.S_addr));
 if (::connect(this->sock2, (const sockaddr*)&hint, sizeof(hint))<0){
     //showConnError("Cannot connect to server");
 }



execFile("gdfg");
return true;
}
