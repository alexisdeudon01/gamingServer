#include "gameboard.h"
#include "ui_gameboard.h"
#include "connserver.h"
#include<QListWidget>
#include <iostream>
#include <string>
#include <QStyle>
#include <QVBoxLayout>
#include <unistd.h>
#include <list>
#include <QPushButton>
#include <QMainWindow>
#include <QSignalMapper>
#include <QAction>
#include <QSignalMapper>
#include <QComboBox>
#include "chessparty.h"
#include <QTableWidget>
#include <thread>
#include <stdio.h>
#include "chesspiece.h"
#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "tower.h"
//https://onlinepngtools.com/create-transparent-png
using namespace std;
ChessParty *chess;
string opponent;
bool continuea=true;
cell Cell;
string messageReceived;
string team;
//Variable pour la partie
bool deplacementEnCours=false;
vector<cell> listPossibilite;
chessPiece *pieceSelection;

vector<string> GameBoard::split(string phrase, string delimiter){
    vector<string> list;
    string s = string(phrase);
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

//loadAllPieces
void recvMsg(ConnServer *myConn,GameBoard *myboard){
    while(true){
        cout<<"hello from thread "<<endl;
        cout<<"opponent is "<<myboard->getOpposent()<<endl;
        string message=myConn->receiveMessage();

        cout<<"We have just received a message from server : "<<message<<endl;
        if(message=="FINDOPPONENT"){
            string message=myConn->receiveMessage();

            cout<<"We have found opponent"<<message<<endl;
            myboard->setOpposent(message);
            opponent=message;
            emit myboard->playerFind();
            //myboard->createBoard(message);
            //break;
        }
        if (message=="CELL CLICKED"){
            cout<<"Your opponent has clicked on a cell"<<endl;
            string test=myConn->receiveMessage().c_str();
            cout<<"cell received is "<<test<<endl;
            int x,y;

            sscanf(test.c_str(),"%i;%i",&Cell.x,&Cell.y);
            cout<<x<<endl;
            emit myboard->userClicked();
        }
        if (message=="UPDATE GAMEBOARD"){
            messageReceived= myConn->receiveMessage();
            cout<<"We have receive a new vision of the board from the server"<<endl;
            emit myboard->getUpdateFromServer();
        }
        if(message=="TEAM SELECTION"){
            string teamMsg=myConn->receiveMessage();
            team=teamMsg;
            if(teamMsg=="true"){
                cout<<"You are the white"<<endl;
            }
            else{
                cout<<"You are the black"<<endl;
            }
            emit myboard->teamSelection();
        }
    }

}
void GameBoard::refreshBoard(){
    vector<string> listFilesMax = split(messageReceived.c_str(), "|");
    cout<<"meesssa is "<<messageReceived<<endl;
    //Delete all elements in vector
    vector<chessPiece *> *allPiece=new vector<chessPiece *>();
    allPiece->reserve(40);
    for(string i : listFilesMax)
    {
        cout<<"i is "<<i<<endl;
        vector<string> details = split(i.c_str(), ",");
        string x=details[0];
        cout<<"x is "<<details.size()<<endl;
        string y=details[1];
        cout<<"y is "<<y<<endl;
        string type=details[2];
        cout<<"type is "<<type<<endl;
        string equipe=details[3];
       /* if( equipe=="true" && type=="King"){
            king *kingOne=new king(chess->getAllCell(),":/kingBlack.png",chess->getTable());
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=kingOne->setCell(Cell);
            chess->setTable(kingOne->getTable());
        }*/
///////////////////////1.Pawn//////////////////////
        //blanc
        if( equipe=="true" && type=="Pawn"){
            pawn *pawnWhite=new pawn(chess->getAllCell(),":/pionBlanc.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=pawnWhite->setCell(Cell,true);
            chess->addPiece(*pawnWhite);
            chess->setTable(pawnWhite->getTable());
            allPiece->push_back(pawnWhite);
        }
        //noir
        if( equipe=="false" && type=="Pawn"){
            pawn *pawnBlack=new pawn(chess->getAllCell(),":/pionNoir.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=pawnBlack->setCell(Cell,false);
            chess->addPiece(*pawnBlack);
            chess->setTable(pawnBlack->getTable());
            allPiece->push_back(pawnBlack);
        }
///////////////////////2.Tower//////////////////////
        //blanc
        if( equipe=="true" && type=="Rook"){
            tower *whiteTower=new tower(chess->getAllCell(),":/tourBlanc.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=whiteTower->setCell(Cell,true);
            chess->addPiece(*whiteTower);
            chess->setTable(whiteTower->getTable());
            //Put another cell
            struct cell CellTwo;
            CellTwo.x=5;
            CellTwo.y=5;
            whiteTower->setCell(CellTwo,true);
            allPiece->push_back(whiteTower);
        }
        //noir
        if( equipe=="false" && type=="Rook"){
            tower *blackTower=new tower(chess->getAllCell(),":/tourNoir.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=blackTower->setCell(Cell,false);
            chess->addPiece(*blackTower);
            chess->setTable(blackTower->getTable());
            allPiece->push_back(blackTower);
        }
////////////////////////3.King///////////////////////
        //blanc
        if( equipe=="true" && type=="King"){
            king *kingWhite=new king(chess->getAllCell(),":/kingBlanc.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=kingWhite->setCell(Cell,true);
            chess->addPiece(*kingWhite);
            chess->setTable(kingWhite->getTable());
            allPiece->push_back(kingWhite);
        }
        //noir
        if( equipe=="false" && type=="King"){
            king *kingBlack=new king(chess->getAllCell(),":/kingBlack.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=kingBlack->setCell(Cell,false);
            chess->addPiece(*kingBlack);
            chess->setTable(kingBlack->getTable());
            allPiece->push_back(kingBlack);
        }
////////////////////////4.Queen///////////////////////
        //blanc
        if( equipe=="true" && type=="Queen"){
            queen *queenWhite=new queen(chess->getAllCell(),":/reineBlanche.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=queenWhite->setCell(Cell,true);
            chess->addPiece(*queenWhite);
            chess->setTable(queenWhite->getTable());
            allPiece->push_back(queenWhite);
        }
        //noir
        if( equipe=="false" && type=="Queen"){
            queen *queenBlack=new queen(chess->getAllCell(),":/reineNoir.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=queenBlack->setCell(Cell,false);
            chess->addPiece(*queenBlack);
            chess->setTable(queenBlack->getTable());
            allPiece->push_back(queenBlack);
        }
////////////////////////5.Bishop///////////////////////
        //blanc
        if( equipe=="true" && type=="Bishop"){
            bishop *bishopWhite=new bishop(chess->getAllCell(),":/fouBlanc.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=bishopWhite->setCell(Cell,true);
            chess->addPiece(*bishopWhite);
            chess->setTable(bishopWhite->getTable());
            allPiece->push_back(bishopWhite);
        }
        //noir
        if( equipe=="false" && type=="Bishop"){
            bishop *bishopBlack=new bishop(chess->getAllCell(),":/fouNoir.png",chess->getTable(),allPiece);
            //Call function
            cell Cell;
            Cell.x=atoi(x.c_str());
            Cell.y=atoi(y.c_str());
            QTableWidgetItem cell=bishopBlack->setCell(Cell,false);
            chess->addPiece(*bishopBlack);
            chess->setTable(bishopBlack->getTable());
            allPiece->push_back(bishopBlack);
        }
////////////////////////6.Knight///////////////////////
                //blanc
                if( equipe=="true" && type=="Knight"){
                    knight *knightWhite=new knight(chess->getAllCell(),":/cavalierBlanc.png",chess->getTable(),allPiece);
                    //Call function
                    cell Cell;
                    Cell.x=atoi(x.c_str());
                    Cell.y=atoi(y.c_str());
                    QTableWidgetItem cell=knightWhite->setCell(Cell,true);
                    chess->addPiece(*knightWhite);
                    chess->setTable(knightWhite->getTable());
                    allPiece->push_back(knightWhite);
                }
                //noir
                if( equipe=="false" && type=="Knight"){
                    knight *knightBlack=new knight(chess->getAllCell(),":/cavalierNoir.png",chess->getTable(),allPiece);
                    //Call function
                    cell Cell;
                    Cell.x=atoi(x.c_str());
                    Cell.y=atoi(y.c_str());
                    QTableWidgetItem cell=knightBlack->setCell(Cell,false);
                    chess->addPiece(*knightBlack);
                    chess->setTable(knightBlack->getTable());
                    allPiece->push_back(knightBlack);
                }
    }
}
void GameBoard::colorCellClicked(){
   //b  chess->colorCell(Cell,Qt::green);

}
void GameBoard::addToWindowTitle(){
    char title[100];
    string monEquipe;
    if (team=="true"){
        monEquipe="white";
    }
    else{
        monEquipe="black";
    }
    sprintf(title,"Chess GameBoard - Connected as %s",this->conServer->getUser().c_str());
    sprintf(title,"%s - %s ",title,monEquipe.c_str());
    this->setWindowTitle(title);
}
GameBoard::GameBoard(QWidget *parent,ConnServer *myConn) :
    QMainWindow(parent),
    ui(new Ui::GameBoard)
{
    char title[100];
    sprintf(title,"Chess GameBoard - Connected as %s",myConn->getUser().c_str());
    this->conServer=myConn;
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->show();

}
void GameBoard::createBoard(){
    chess->createParty(opponent);
    chess->createBoard();
}
GameBoard::~GameBoard()
{
    delete ui;
}
void GameBoard::hideLabel(){
    this->ui->waitingPlayer->hide();
}
void GameBoard::createWindowPlayer(){
    this->windowPlayer = new QWidget;
    this->layoutPlayer = new QVBoxLayout(this);
    this->windowPlayer->setWindowTitle("Choose a player ...");
}
void GameBoard::showWindow(){
    windowPlayer->setLayout(this->layoutPlayer);
    windowPlayer->show();
}
void GameBoard::setOpposent(string op){
    this->opposent=op;
}
void GameBoard::ListPlayerGUI(std::list<std::string> listPlayer){
    //create party
    chess=new ChessParty(this->conServer,this);
    std::thread t1{recvMsg,this->conServer,this};
    t1.detach();
    QObject::connect(this, SIGNAL(playerFind()),this,SLOT(createBoard()));
    QObject::connect(this, SIGNAL(userClicked()),this, SLOT(colorCellClicked()));
    QObject::connect(this, SIGNAL(getUpdateFromServer()),this, SLOT(refreshBoard()));
    QObject::connect(this, SIGNAL(teamSelection()),this, SLOT(addToWindowTitle()));
    if (listPlayer.size()>1){
        this->box=new QComboBox(this->windowPlayer);
        for(std::list<std::string>::const_iterator i = listPlayer.begin(); i != listPlayer.end(); ++i)
        {
          this->box->addItem(i->c_str());
        }
        this->layoutPlayer->addWidget(this->box);
        QPushButton *select=new QPushButton("Select");
        this->layoutPlayer->addWidget(select);
        QObject::connect(select,SIGNAL(clicked()),this,SLOT(playerChoose()));
        showWindow();
      }
        else{
        std::string firstStr = listPlayer.front();
            if(firstStr=="false"){

            }
            else{
                showConnError(firstStr);
                this->windowPlayer->hide();
                //Tell server that I want to play with player 'firstStre'
                this->conServer->sendMsg("PLAYWITH\n");
                opponent=firstStr;
                char userrt[100];
                sprintf(userrt,"%s\n",firstStr.c_str());
                this->conServer->sendMsg(userrt);
                this->opposent=firstStr;
                chess->createParty(firstStr.c_str());
                chess->createBoard();
                continuea=false;
            }
        }
}
void GameBoard::showConnError(string message){
    QMessageBox messageBox;
    messageBox.critical(0,"Error",message.c_str());
    messageBox.setFixedSize(500,200);
}
string GameBoard::getOpposent(){
    return this->opposent;
}
void GameBoard::playerChoose(){
    QString result=this->box->currentText();
    this->opposent=result.toStdString();
    this->windowPlayer->hide();
    //Tell server that I want to play with player 'firstStre'
    this->conServer->sendMsg("PLAYWITH\n");
    char user[100];
    sprintf(user,"%s\n",result.toStdString().c_str());
    this->conServer->sendMsg(user);
    chess->createParty(user);
}
inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

//slots that detect a cell pressed
void GameBoard::onTableClicked(const QModelIndex &index)
{
    if(deplacementEnCours){
        int x=index.row();
        int y=index.column();
        struct cell CellPossible;
        CellPossible.x=x;
        CellPossible.y=y;
        bool find=false;
        for (cell cellIt : listPossibilite){
            if(cellIt.x==x && cellIt.y==y){
                find=true;
                cout<<"deplacement autorise"<<endl;

                pieceSelection->setCell(cellIt,pieceSelection->getTeam());
                deplacementEnCours=false;
                pieceSelection->desactivatePossibleDeplacement(&listPossibilite);
            }
        }
        if(find){
            cout<<"Le deplacement est autorisé"<<endl;
        }
        //check If cell on which user wants to move the piece is allowed
    }
    chessPiece *pieceClick=chess->getPieceByXY(index.row(),index.column());

    if(pieceClick!=NULL){
        /*string s = typeid(pieceClick).name();
        cout<<"Class if type of "<<s<<endl;
        cout<<"piece is"<<pieceClick->getTypePiece()<< "of team  "<<pieceClick->getTeam()<<endl;
        cout<<"You have clicked on "<<index.row()<<","<<index.column()<<endl;*/
        if(pieceClick->getTypePiece()=="pawn" && team==BoolToString(pieceClick->getTeam())){
            deplacementEnCours=true;
            //activate lock which is cell selected
            pawn* p = static_cast<pawn*>(pieceClick);
            p->activatePossibleDeplacement();
            pieceSelection=p;
            listPossibilite=*p->getAvailableDeplc();
        }
    }

    this->conServer->sendMsg("TRANSMITMSG\n");
    char op[100];
    sprintf(op,"%s\n",this->opposent.c_str());
    this->conServer->sendMsg(op);
    this->conServer->sendMsg("CELL CLICKED\n");
    char cmd[100];
    sprintf(cmd,"%s;%s\n",to_string(index.row()).c_str(),to_string(index.column()).c_str());
    this->conServer->sendMsg(cmd);
   // showConnError("clicked detected\n");
  /*  if (index.isValid()) {
        QString cellText = index.data().toString();

        cout<<"You have clicked on "<<cellText.toStdString();
    }*/
}


