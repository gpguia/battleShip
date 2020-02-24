#include "board.h"

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

Board* setShipPos(Board *b, Coordinate s, Coordinate e){
    int x = (e.row - s.row);
    int y = (e.col - s.col);

    if((s.row > b->rowSize || s.col > b->colSize) || (e.col > b->colSize || e.row > b->rowSize))
        return b;

    if((s.row < 0 || s.col < 0) || (e.col < 0 || e.row < 0))
        return b;

    printf("x: %d\n",x);
    printf("y: %d\n",y);
    if(x > 5 || y > 5){
        return b;
    }

    if(y == 0){ //horizontal
        for(int i=0;i<e.row;i++){
            b->board[s.row][i] = 1;
        }
    }else if(x == 0){//vertical
        for(int j=0;j<e.col;j++){
            b->board[j][s.col] = 1;
        }
    }
    return b;
}


void randomPlaceShips(Board *b){
    int x,y, pos[5];
    Coordinate start;
    srand(time(0));
    
    for(int i=0;i<5;i++){ //randomize number to choose the way the ship will be put
        pos[i] = rand();
    }
    if(pos[0] % 2 == 0){//CARRIER will be horizontal
        x = (rand() % (b->rowSize + 1));
        y = (rand() % (b->rowSize + 1));
        if(x + 5 <= b->rowSize){

        }
    }else{

    }
    printf("x: %d\n",x);
    printf("y: %d\n",y);

}