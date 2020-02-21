#include "include/battleShip.h"

int main (void){
    Board *b = newBoard(10,12);
    printf("%d\n",b->board[0][0]);
    return 0;
}
