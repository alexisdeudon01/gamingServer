#include "king.h"

king::king(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable,vector<chessPiece *> *Allcell) : chessPiece(cell,imgLocation,mytable,Allcell)
{
this->type="king";
}
void king::activatePossibleDeplacement(){

}
