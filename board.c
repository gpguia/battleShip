#include "board.h"
#include "ships.h"

Board* newBoard(int row, int col){
    Board *b = malloc(sizeof (Board));

    b->rowSize = row;
    b->colSize = col;
    b->board = (int **)malloc(row * sizeof(int*));

    for(int i = 0; i < row; i++) {
        b->board[i] = (int *)malloc(col * sizeof(int));
    }
    for(int i=0; i<row; i++){
        for(int j=0;j<col; j++){
            b->board[i][j] = -1;
        }
    }
    return b;
}

void clearBoard(Board* b){    
    for(int i=0; i<b->rowSize; i++){
        free(b->board[i]);
    }
    free(b);
}