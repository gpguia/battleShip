#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Board{
    int **board;
    int rowSize;
    int colSize;
} Board;



Board* newBoard(int row, int col);
void clearBoard(Board* b);
