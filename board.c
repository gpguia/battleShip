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

bool isValidPos(Board* b, Ship ship){
    if(ship.start.col < 0 || ship.start.row < 0){
        return false;
    }

    if(ship.isHorizontal){
        if(ship.length + ship.start.col > b->colSize){
            return false;
        }
    }else{
        if(ship.length + ship.start.row > b->rowSize){
            return false;
        }
    }

    for(int i = 0; i < ship.length - 1; i++){
        if(ship.isHorizontal){
            if(b->board[ship.start.row][ship.start.col + i] != -1 && (ship.start.col + i) < b->colSize) // -1 is water
                return false;
        }else{//vertical
            if(b->board[ship.start.row + i][ship.start.col] != -1 && (ship.start.row + i) < b->rowSize) // -1 is water
                return false;
        }
    }
    return true;
}

bool setShipPos(Board *b, Ship ship){

    if(!isValidPos(b,ship)){
        // printf("ERROR: This is an invalid POS :(\n");
        return false;
    }

    if(ship.isHorizontal){ //horizontal
        for(int i=0;i<ship.length;i++){
            b->board[ship.start.row][ship.start.col + i] = ship.type;
        }
    }else{//vertical
        for(int j=0;j<ship.length;j++){
            b->board[ship.start.row + j][ship.start.col] = ship.type;
        }
    }
    return true;
}

Board* shoot(Board *plAtirador, Board *plAdvers, Coordinate shot){
	if(plAdvers->board[shot.row][shot.col]==0 || plAdvers->board[shot.row][shot.col]==1 || plAdvers->board[shot.row][shot.col]==2 || plAdvers->board[shot.row][shot.col]==3 || plAdvers->board[shot.row][shot.col]==4)
		plAtirador->board[shot.row][shot.col]=5;
	else if(plAdvers->board[shot.row][shot.col]==-1)
		plAtirador->board[shot.row][shot.col]=6;	
}

void printBoard(Board *b){
	

	for(int i=0;i<b->rowSize;i++){
		printf("\t%d|",i);
		for(int j=0;j<b->colSize;j++){
      		if(b->board[i][j]==-1)
        		printf(" ~ |");
        	if(b->board[i][j]==BOAT_SHOT)   //5 significa que algum barco foi atingido
        		printf(" ⊗ |");
        	if(b->board[i][j]==WATER_SHOT)   //6 significa que acertou na agua
        		printf(" X |");
      		else if(b->board[i][j] == 0 || b->board[i][j] == 1 || b->board[i][j] == 2 || b->board[i][j] == 3 ||b->board[i][j] == 4 )
        	printf(" O |");
    }
		printf("\n");
	}

	printf("\t   ");
	for(int k=0;k<b->colSize;k++){
		printf("%d | ",k);
	}
	printf("\n");
}




void randomPlaceShips(Board *b){
    Ship s1,s2,s3,s4,s5;
    Coordinate s;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    bool isNotOnBoard = true;

    s1.isAlive = true;
    s1.length = CARRIER_SIZE;
    s1.type = CARRIER;
    while(isNotOnBoard){
        s1.start.row = (rand() % (b->rowSize - CARRIER_SIZE));
        s1.start.col = (rand() % (b->colSize - CARRIER_SIZE));
        s1.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s1);
        if(aux == true){
            isNotOnBoard = false;
        }
    }

    // printBoard(b);

    isNotOnBoard = true;
    s2.isAlive = true;
    s2.length = BATTLESHIP_SIZE;
    s2.type = BATTLESHIP;
    while(isNotOnBoard){
        s2.start.row = (rand() % (b->rowSize - BATTLESHIP_SIZE));
        s2.start.col = (rand() % (b->colSize - BATTLESHIP_SIZE));
        s2.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s2);
        if(aux == true)
            isNotOnBoard = false;
    }

    isNotOnBoard = true;
    s3.isAlive = true;
    s3.length = CRUSIER_SIZE;
    s3.type = CRUISER;
    while(isNotOnBoard){
        s3.start.row = (rand() % (b->rowSize - CRUSIER_SIZE));
        s3.start.col = (rand() % (b->colSize - CRUSIER_SIZE));
        s3.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s3);
        if(aux == true)
            isNotOnBoard = false;
    }

    isNotOnBoard = true;
    s4.isAlive = true;
    s4.length = SUBMARINE_SIZE;
    s4.type = SUBMARINE;
    while(isNotOnBoard){
        s4.start.row = (rand() % (b->rowSize - SUBMARINE_SIZE));
        s4.start.col = (rand() % (b->colSize - SUBMARINE_SIZE));
        s4.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s4);
        if(aux == true)
            isNotOnBoard = false;
    }

    isNotOnBoard = true;
    s5.isAlive = true;
    s5.length = DESTROYER_SIZE;
    s5.type = DESTROYER;
    while(isNotOnBoard){
        s5.start.row = (rand() % (b->rowSize - DESTROYER_SIZE));
        s5.start.col = (rand() % (b->colSize - DESTROYER_SIZE));
        s5.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s5);
        if(aux == true)
            isNotOnBoard = false;
    }
}
