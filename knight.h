#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class knight : public chessPiece
{
public:
    knight(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *Allcell );
    void activatePossibleDeplacement();
};

#endif // KNIGHT_H
