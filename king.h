#ifndef KING_H
#define KING_H

#include "chesspiece.h"
class king : public chessPiece
{
public:
    king(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *Allcell );
    void activatePossibleDeplacement();
};

#endif // KING_H
