#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QMainWindow>
#include "connserver.h"
#include <QVBoxLayout>
#include <QComboBox>
 #include<iostream>
#include <vector>
using namespace std;
namespace Ui {
class GameBoard;
}

class GameBoard : public QMainWindow
{
    Q_OBJECT
signals:
    void playerFind();
    void userClicked();
    void getUpdateFromServer();
    void teamSelection();
public:
    void hideLabel();
    explicit GameBoard(QWidget *parent = nullptr,ConnServer *myConn= nullptr);
    ~GameBoard();
    void ListPlayerGUI(list<string> listPlayer);
    void createWindowPlayer();
     void showWindow();
    void showConnError(string message);
    std::string getOpposent();
    void setOpposent(string op);
    vector<string> split(string phrase, string delimiter);
public slots:
     void playerChoose();
     void createBoard();
     void onTableClicked(const QModelIndex &index);
     void colorCellClicked();
     void refreshBoard();
     void addToWindowTitle();
private:
    Ui::GameBoard *ui;
    ConnServer *conServer;
    QWidget *windowPlayer;
    QVBoxLayout *layoutPlayer;
     QComboBox *box;
    string opposent;
};

#endif // GAMEBOARD_H
