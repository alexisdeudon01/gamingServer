#ifndef TOWER_H
#define TOWER_H

#include "chesspiece.h"

class tower : public chessPiece
{
public:
    tower(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *Allcell );
    void activatePossibleDeplacement();
};

#endif // TOWER_H
