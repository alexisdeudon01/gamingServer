#include "connserver.h"



#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
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
#include <string>
#include <QMainWindow>
#include <QScrollBar>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include<algorithm>
using namespace std;

ConnServer::ConnServer(Ui::MainWindow *ui)
{
this->ui=ui;

}
ConnServer::~ConnServer(){
    cout<<"Cleanup"<<endl;
    WSACleanup();
    closesocket(this->sock);
}
string ConnServer::findFreePlayers(){
    char cmd1[]="GETLISTFREEPLAYER\n";
    cout<<"1"<<endl;
    sendMsg(cmd1);
     char pass[100];
     char cmd2[]="GAME Chess\n";
    sendMsg(cmd2);
    string response=receiveMessage();
    //list<string> decom=decomposePlayer(response);
    return response;
}

string ConnServer::receiveMessage()
{
    char buffer[4096];
    std::string myString;
    int nDataLength;
    nDataLength = recv(this->sock, buffer, sizeof(buffer), 0);
    cout<<"message2"<<buffer<<endl;
    myString.append(buffer, nDataLength);
    return myString ;
}

void ConnServer::sendMsg(char* msg)
{
        cout<<"2"<<endl;
  if(! send(this->sock,msg,strlen(msg),0)){
    showConnError("Cannot send  data");
  }
      cout<<"3"<<endl;
}

void ConnServer::showConnError(string message){
    QMessageBox messageBox;
    messageBox.critical(0,"Error",message.c_str());
    messageBox.setFixedSize(500,200);
}
list<string> ConnServer::decomposePlayer(string responseServer){
    std::string delimiter = ",";

    size_t pos = 0;
    std::string token;
    list<string> mylist;
    list<string>::iterator it = mylist.begin();
    int i=0;
    while ((pos = responseServer.find(delimiter)) != std::string::npos) {
        token = responseServer.substr(0, pos);
        std::cout << "P1"<<token << std::endl;
        mylist.insert(it,token);
        responseServer.erase(0, pos + delimiter.length());
        i++;
}
   // res[i+1]=responseServer;
    return mylist;
}

bool ConnServer::ConnectToServer(char* ip,char* port, char* username, char* password){
    //Initialise winsock
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2,2);

    if(WSAStartup(DllVersion, &wsaData)!=0)
        showConnError("Can't initialize winsock");
    //Create a socket
    this->sock=socket(AF_INET,SOCK_STREAM,0);
    if (this->sock == INVALID_SOCKET)
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
 sockaddr_in hint;
 ZeroMemory(&hint, sizeof(hint));
 hint.sin_family=AF_INET;
 hint.sin_port=htons(2401);
 memcpy(&hint.sin_addr.S_un.S_addr,host->h_addr_list[0], sizeof(hint.sin_addr.S_un.S_addr));
 if (::connect(sock, (const sockaddr*)&hint, sizeof(hint))!=0)
     showConnError("Cannot connect to server");
 char user[100];
 //Concat and send user
 sprintf(user,"USER %s\n",username);
 sendMsg("AUTH\n");
 sendMsg(user);
 //Concat and send password
 //Becarefull, it is not hash
 char pass[100];
 sprintf(pass,"PASS %s\n",password);
 sendMsg(pass);
 //Concat and send admin false
 //Becarefull, it is not hash
  char szMsg3[]="ADMIN false\n";
  sendMsg(szMsg3);
  sendMsg("GAME Chess\n");
  //Receive response
 string szTemp=receiveMessage();
 if (szTemp=="Wrong credentials"){
     ui->label_3->setVisible(true);
 }
 if (szTemp=="Credential OK"){
     //Disable label claming wrong credential
     ui->label_3->setVisible(false);
    //StartChess Gaming
     //Gathered list game
    this->user=username;
     return true;
 }
    return false;
}
string ConnServer::getUser(){
    return this->user;
}
