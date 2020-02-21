#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Board{
    int **board;
    int r;
    int c;
} Board;

Board* newBoard(int n, int m);
