
#include "chesspiece.h"
#include <QTableWidgetItem>
#include <string>
#include <iostream>
#include "Cell.h"
chessPiece::chessPiece(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *Allcell )
{
    //copy gameboard cell in order to access further
    this->chessboard=cell;
    this->imagePath=imgLocation;
    this->board=mytable;
    this->x=-1;
    this->y=-1;
    this->type="None";
    this->Cell.x=-1;
    this->AllCell=Allcell;
}
void chessPiece::colorCell(cell Cell,const QBrush &brush){
   //Need to convert x,y into array index
    //0 1 2 3 4
    //5 6(1,1) 7 8 9
    //On remplit de gauche a droite
    //index i=10*x+y
    int i=10*Cell.x+Cell.y;
    //QTableWidgetItem *newItem=new QTableWidgetItem();
    //newItem=&this->AllCellsPTr[i];
    QModelIndex* index=new QModelIndex();
    this->board->item(Cell.x,Cell.y)->setBackground(brush);
    //this->myTable->itemFromIndex(index->sibling(x,y))->setBackground(Qt::green);
    //newItem->setBackground(Qt::green);
    //this->myTable->setItem(x,y,newItem);
}
void chessPiece::ColorMtplCell(vector<cell> allCells,const QBrush &brush){
       for(cell i : allCells)
       {
            colorCell(i,brush);
       }

}
chessPiece::~chessPiece(){

}

void chessPiece::desactivatePossibleDeplacement(vector<cell> *selectedCell) {
    //QColor color;
    //color.fromRgb(232, 235, 239);
    for(cell currentCell : *selectedCell){
        cout<<"Delete cell ("<<x<<","<<y<<endl;
        int posX=currentCell.x;
        int posY=currentCell.y;
        if(((posX)+(posY)) % 2 ){
            this->board->item(posX, posY)->setBackground(Qt::lightGray);
        }
        else{
            this->board->item(posX, posY)->setBackground(Qt::white);
        }

    }
}


QTableWidget* chessPiece::getTable(){
    return this->board;
}

bool chessPiece::checkIfPiece(){
    if (this->Cell.x==-1){
        return false;
    }
    return true;
}
QTableWidgetItem chessPiece::setCell(cell Cell, bool team){
    this->Cell=Cell;
    this->team=team;
    //Link to chess party
    if( x!=-1){
       deleteImage();
    }
    QImage *img=loadImage();
    int i=8*Cell.x+Cell.y;
    QTableWidgetItem *cell=&(this->chessboard[i]);
    this->board->item(Cell.x,Cell.y)->setData(Qt::DecorationRole , QPixmap::fromImage(*img));
    this->board->item(Cell.x,Cell.y)->setTextAlignment(Qt::AlignHCenter);

    this->x=Cell.x;
    this->y=Cell.y;
    return *cell;
//    /this->chessboard[i]=cell;
//    /deleteImage();
    //call loadImage
}
string chessPiece::getTypePiece(){
    //return "None";
    return this->type;
}
cell chessPiece::getCell(){
    return this->Cell;
}
bool chessPiece::getTeam(){
    return this->team;
}

//erased image from cell
//should be private
void chessPiece::deleteImage(){
    this->board->item(this->x,this->y)->setData(Qt::DecorationRole ,NULL);
  /*  int i=8*this->x+this->y;
    QTableWidgetItem *newCell=new QTableWidgetItem();
    int posX=this->x-1;
    int posY=this->y-1;
    if(((posX)+(posY)) % 2 ){
    newCell->setBackground(Qt::black);
    }
    else{
        newCell->setBackground(Qt::white);
    }
    cout<<"7"<<endl;
   this->chessboard[i]=*newCell;*/
}

//load image from cell
//should be private
QImage* chessPiece::loadImage(){
    QImage *img = new QImage();
    bool loaded = img->load(this->imagePath.c_str());
    return img;
}
//QString imgPath = "C:\\path\\to\\image.jpg";
//QImage *img = new QImage();
//bool loaded = img->load("C:\\Users\\adeudon\\Documents\\ChessClient\\chess.jpg");
//item1->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
