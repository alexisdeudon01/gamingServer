#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class pawn : public chessPiece
{

public:
    pawn(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *Allcell );
   void activatePossibleDeplacement();
    bool checkIfPieceForDeplacement(int x, int y);
    vector<cell>* getAvailableDeplc();
    void desactivatePossibleDeplacement();
};

#endif // PAWN_H
