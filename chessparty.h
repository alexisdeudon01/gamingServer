#ifndef CHESSPARTY_H
#define CHESSPARTY_H

#include "connserver.h"
#include "gameboard.h"
#include <string>
#include <QTableWidget>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "chesspiece.h"

class ChessParty
{
public:
    ChessParty(ConnServer *myConn,GameBoard *myBoard);
    void createParty(std::string player);
    void createBoard();
    void setSizeChessGamePlay();
    void setColorChessGamePlay();
    void colorBoard();
    void colorCell(cell Cell,const QBrush &brush);
    void refreshBoard();
    QTableWidget* getTable();
    QTableWidgetItem * getAllCell();
    void setTable(QTableWidget* table);
    void ColorMtplCell(vector<cell> allCells,const QBrush &brush);
    void addPiece(chessPiece piece);
    //return null if nothing
    chessPiece* getPieceByXY(int x, int y);
private:
    ConnServer *myConn;
    GameBoard *myBoard;
    QVBoxLayout *chessLayout;
    QTableWidget *myTable;
    QTableWidgetItem *AllCellsPTr;
    std::vector<chessPiece> AllCellWithPieces;
};

#endif // CHESSPARTY_H
