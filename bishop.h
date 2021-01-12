#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class bishop : public chessPiece
{
public:
    bishop(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *AllCell );
    void activatePossibleDeplacement();
};

#endif // BISHOP_H
