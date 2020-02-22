#include "board.h"

Board* newBoard(int row, int col){
    Board *b = malloc(sizeof (Board));
    b->c = col;
    b->r = row;
    b->board = (int **)malloc(row * sizeof(int*));

    for(int i = 0; i < row; i++) {
        b->board[i] = (int *)malloc(col * sizeof(int));
    }
    for(int i=0; i<row; i++){
        for(int j=0;j<col; j++){
            b->board[i][j] = 0;
        }
    }
    return b;
}