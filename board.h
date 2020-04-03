#include "utils.h"

#define MAXNUMSHIPS 16
typedef struct _Coordinate{
    int row;
    int col;
}Coordinate;

enum ShipType{
    CARRIER,  //0
    BATTLESHIP, //1
    CRUISER,   //2
    SUBMARINE,  //3
    DESTROYER,  //4
    TSHAPE,  //5
    GOODSHOT //if this boat has been hit.
};

typedef struct _Shots{
    Coordinate target;
    bool isHit;
    struct _Shots* next;
} Shots;

typedef struct _PiceBoard{
    bool hasShip;
    bool wasHit;
    int shipType;
} PiceBoard;

typedef struct _Board{
    PiceBoard **board;
    int rowSize;
    int colSize;
    Shots* shotsFierd;
} Board;

void newBoard(int row, int col, Board* p1, Board* p2);
void clearBoard(Board* b);

void printBoard(Board *b);
void printAllShipsTypes();

int* selectChips(int row, int col);
bool isValidPos(Board*b, int type, Coordinate start);
void setShips(Board* b, int* lst);