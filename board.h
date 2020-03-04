#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "ships.h"

#define BOAT_SHOT 5
#define WATER_SHOT 6
#define MAX_NUM_SHIPS 5

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

struct _Shots{
    Coordinate target;
    struct _Shots* next;
};
typedef struct _Shots Shots;

typedef struct _Board{
    int **board;
    int rowSize;
    int colSize;
    Ship ships[MAX_NUM_SHIPS];
    int curQtdShips;
    Shots* shotsFierd;
} Board;

Shots* newShot(Shots* lst, Coordinate s);
void delAllShots(Shots *lst);
void printShots(Shots* lst);
Shots* searchShot(Shots* lst, Coordinate k);

Board* newBoard(int row, int col);
void clearBoard(Board* b);

void shoot(Board *b, Coordinate shot, int turn);
bool isAWaterShot(Board* b, Coordinate t);

void randomPlaceShips(Board *b);
bool setShipPos(Board *b, Ship ship);
bool isValidPos(Board* b, Ship ship);

void printBoard(Board* b);