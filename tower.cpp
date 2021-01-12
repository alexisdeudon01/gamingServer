#include "tower.h"

tower::tower(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable,vector<chessPiece *> *Allcell) : chessPiece(cell,imgLocation,mytable,Allcell)
{
this->type="tower";
}
void tower::activatePossibleDeplacement(){

}
