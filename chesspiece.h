#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QTableWidgetItem>
#include <string>
#include "Cell.h"


using namespace std;
class chessPiece
{
public:

    chessPiece(QTableWidgetItem *cell,string imgLocation, QTableWidget *mytable, vector<chessPiece *> *AllCell );
    ~chessPiece();
    //transpose piece to cell x,y

    QTableWidgetItem setCell(cell Cell, bool team);
    QImage* loadImage();
    QTableWidget* getTable();
    bool checkIfPiece();
    cell getCell();
    string getTypePiece();
    bool getTeam();
    void colorCell(cell Cell,const QBrush &brush);
    void ColorMtplCell(vector<cell> allCells,const QBrush &brush);
    void desactivatePossibleDeplacement(vector<cell> *selectedCell);
protected:

    void deleteImage();
    //Gameboard cell reference
    QTableWidgetItem *chessboard;
    //link to image path
    string imagePath;
    //Gameboard cell reference
    QTableWidget *board;
    int x;
    int y;
    bool team;
    cell Cell;
    string type;
    vector<chessPiece *> *AllCell;
    vector<cell> *selectedCell;
};

#endif // CHESSPIECE_H
