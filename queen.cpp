#include "queen.h"

queen::queen(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable,vector<chessPiece *> *Allcell) : chessPiece(cell,imgLocation,mytable,Allcell)
{
this->type="queen";
}
void queen::activatePossibleDeplacement(){

}
