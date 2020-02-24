#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "ships.h"

typedef struct _Board{
    int **board;
    int rowSize;
    int colSize;
} Board;



Board* newBoard(int row, int col);
void clearBoard(Board* b);

void randomPlaceShips(Board *b);
Board* setShipPos(Board *b, Coordinate s, Coordinate e);