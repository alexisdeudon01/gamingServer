#include "knight.h"

knight::knight(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable,vector<chessPiece *> *Allcell) : chessPiece(cell,imgLocation,mytable,Allcell)
{
this->type="knight";
}
void knight::activatePossibleDeplacement(){

}
