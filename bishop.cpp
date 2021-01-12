#include "bishop.h"
bishop::bishop(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *Allcell ) : chessPiece(cell,imgLocation,mytable,Allcell)
{
    this->type="bishop";
}
void bishop::activatePossibleDeplacement(){

}
