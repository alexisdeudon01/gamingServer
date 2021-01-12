#include "chessparty.h"
#include "pawn.h"
#include <iostream>
using namespace std;
pawn::pawn(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable,vector<chessPiece *> *Allcell) : chessPiece(cell,imgLocation,mytable,Allcell)
{
this->type="pawn";
}
void pawn::activatePossibleDeplacement() {
   // this->selectedCell=NULL;
    //this->selectedCell->reserve(1);
    cout<<"it works yah yej"<<endl;
    cell CellTwo;
    if(checkIfPieceForDeplacement(this->Cell.x-1,this->Cell.y)){
        CellTwo.x=this->Cell.x-1;
        CellTwo.y=this->Cell.y;
        this->colorCell(CellTwo,Qt::red);
    }
    vector<cell> r;
    r.push_back(CellTwo);
    this->selectedCell=&r;
}

//Implement extreme map case
bool pawn::checkIfPieceForDeplacement(int x, int y){
    for(chessPiece* piece : *this->AllCell){

        cell myCell=piece->getCell();
        cout<<"Piece on x : "<<myCell.x<<" y : "<<myCell.y<<endl;
        if(myCell.x==x&&myCell.y==y){
            return false;
        }
    }
    return true;
}
vector<cell>* pawn::getAvailableDeplc(){
    return this->selectedCell;
}
