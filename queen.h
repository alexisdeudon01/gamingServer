#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class queen : public chessPiece
{
public:
    queen(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *Allcell );
    void activatePossibleDeplacement();
};

#endif // QUEEN_H
