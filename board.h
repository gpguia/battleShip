#include "ship.h"

typedef struct _Board{
    Cell **board;
    int rowSize;
    int colSize;
    Shots* shotsFierd;
    int hp;
} Board;


void newBoard(int row, int col, Board* p1, Board* p2);
void clearBoard(Board* b);
void setHP(Board* p1, Board* p2, int* lstOfShips);

void printBoard(Board *b);
void printAllShipsTypes();

int* selectShips(int row, int col);
bool isValidPos(Board* b, Ship ship);
bool setShip(Board *b, Ship ship);
void randomPlaceShips(Board *b, int* lstOfShips);
void manualyPlanceShips(Board* b, int* lstOfShips);
int convertRotation(int rot);
Shots* newShot(Shots* lst, Coordinate s, bool isHit);
void clearShots(Shots *lst);
Shots* searchShot(Shots* lst, Coordinate k);
void fire(Board* p1board, Board* p2board);
void printShots(Shots* lst);