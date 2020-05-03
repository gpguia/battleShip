#include "utils.h"

#define MAXNUMSHIPS 16
#define CARRIER_SIZE 5
#define TSHAPE_SIZE 3 //+2 for the front part
#define BATTLESHIP_SIZE 4
#define CRUSIER_SIZE 3
#define SUBMARINE_SIZE 3
#define DESTROYER_SIZE 2
#define ROTATION_0 0
#define ROTATION_90 1
#define ROTATION_180 2
#define ROTATION_270 3

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
    GOODSHOT, //hit the target
    WATERSHOT
};

typedef struct _Shots{
    Coordinate target;
    bool isHit;
    struct _Shots* next;
} Shots;

typedef struct _Cell{
    bool hasShip;
    bool wasHit;
    int shipType;
} Cell;

typedef struct _Ship{
    int type;
    int length;
    Coordinate start;
    int rotation;
} Ship;

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