#include "chessparty.h"
#include "gameboard.h"
#include <string>
#include <QTableWidget>
#include <iostream>
#include <QtWidgets>
#include "Cell.h"
#include "chesspiece.h"
#include <vector>
//*https://wiki.qt.io/How_to_Use_QTableWidget
using namespace std;
ChessParty::ChessParty(ConnServer *myConn, GameBoard *board)
{
    this->myConn=myConn;
    this->myBoard=board;
    this->chessLayout=new QVBoxLayout(this->myBoard);
    this->AllCellsPTr=new QTableWidgetItem[101];
  //  this->AllCellWithPieces=new cell[16];
}

void ChessParty::createParty(string opponent){
    string cmd="CREATE GAMEPLAY\n";
    string me=this->myConn->getUser();
    cout<<"A party will be created with "<<me<<" and "<<opponent<<endl;
    createBoard();
}
void  ChessParty::addPiece(chessPiece piece){
    this->AllCellWithPieces.push_back(piece);
}

chessPiece* ChessParty::getPieceByXY(int x, int y){
    int index=0;
    for (chessPiece piece : this->AllCellWithPieces){
        cout<<"Piece on chess is ("<<piece.getCell().x<<","<<piece.getCell().y<<") vs coordinates by user ("<<x<<","<<y<<")"<<endl;
        if (piece.getCell().x==x && piece.getCell().y==y){
            return &this->AllCellWithPieces[index];
        }
    index++;
    }
    return NULL;
//iterate over all pieces, compare x,y of Cell, if match return piece
    //if no match return null
}
void ChessParty::setSizeChessGamePlay(){
    int i=0;
    while(i<10){
        this->myTable->setColumnWidth(i,75);
        i++;
    }
    i=0;
    while(i<10){
        this->myTable->setRowHeight(i,75);
        i++;
    }

    this->myBoard->setFixedWidth((8*75)+50);
    this->myBoard->setFixedHeight((8*75)+50);
}
void ChessParty::ColorMtplCell(vector<cell> allCells,const QBrush &brush){
       for(cell i : allCells)
       {
            colorCell(i,brush);
       }

}
void ChessParty::colorCell(cell Cell,const QBrush &brush){
   //Need to convert x,y into array index
    //0 1 2 3 4
    //5 6(1,1) 7 8 9
    //On remplit de gauche a droite
    //index i=10*x+y
    int i=10*Cell.x+Cell.y;
    //QTableWidgetItem *newItem=new QTableWidgetItem();
    //newItem=&this->AllCellsPTr[i];
    QModelIndex* index=new QModelIndex();
    this->myTable->item(Cell.x,Cell.y)->setBackground(brush);
    //this->myTable->itemFromIndex(index->sibling(x,y))->setBackground(Qt::green);
    //newItem->setBackground(Qt::green);
    //this->myTable->setItem(x,y,newItem);
}
void ChessParty::setTable(QTableWidget* table){
    this->myTable=table;
}
void ChessParty::createBoard(){
    this->myBoard->hideLabel();
    this->myBoard->show();
    this->myTable=new QTableWidget(this->myBoard);
    this->myTable->setColumnCount(8);
    this->myTable->setRowCount(8);
    this->myTable->setMinimumHeight(this->myBoard->size().height());
    this->myTable->setMinimumWidth(this->myBoard->size().width());
    setSizeChessGamePlay();
    this->myTable->setSelectionMode(QAbstractItemView::NoSelection);
    this->myTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->myTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->myTable->setShowGrid(true);
    this->myTable->show();
    //setColorChessGamePlay();
    QObject::connect(this->myTable, SIGNAL(clicked(const QModelIndex &)), this->myBoard, SLOT(onTableClicked(const QModelIndex &)));

    //Board has been created so the player is not free anymore, we update the database
    this->myConn->sendMsg("UPDATEPLAYERTOBUSY\n");
    char user[100];

    string usera=this->myConn->getUser().c_str();
    char* c = strcpy(new char[usera.length() + 1], usera.c_str());
    sprintf(user,"%s\n",c);
    this->myConn->sendMsg(user);
    colorBoard();
}
QTableWidgetItem* ChessParty::getAllCell(){
    return this->AllCellsPTr;
}
QTableWidget* ChessParty::getTable(){
    return this->myTable;
}


void ChessParty::colorBoard(){
    int i=0;
    int posX=0;
    int posY=0;
    //QColor color;
    //color.fromRgb(232, 235, 239);
    while(posX!=8 ){

        QTableWidgetItem *item1=new QTableWidgetItem();
        //QString imgPath = "C:\\path\\to\\image.jpg";
        //QImage *img = new QImage();
        //bool loaded = img->load("C:\\Users\\adeudon\\Documents\\ChessClient\\chess.jpg");
        //item1->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
        cout<<"x: "<<posX<<", y"<<posY<<endl;
        if(((posX)+(posY)) % 2 ){
            this->myTable->setItem(posX,posY,item1);
            this->myTable->item(posX, posY)->setBackground(Qt::lightGray);
        }
        else{
            cout<<"4"<<endl;
            this->myTable->setItem(posX,posY,item1);
            this->myTable->item(posX, posY)->setBackground(Qt::white);
        }
        if(posY>=7){
            cout<<"1"<<endl;

         posY=0;
         posX++;
        }
        else{
            cout<<"2"<<endl;
            posY++;
        }
        this->AllCellsPTr[i]=*item1;
        i++;
    }
}
