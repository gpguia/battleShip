#include "board.h"

int turn1=0;
int turn2=0;

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
    b->shotsFierd = NULL;
    b->lstOfShips = NULL;
    return b;
}

void clearBoard(Board* b){
    for(int i=0; i<b->rowSize; i++){
        free(b->board[i]);
    }
    clearShips(b->lstOfShips);
    clearShots(b->shotsFierd);
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

    if(ship.type == TSHAPE){
        if(ship.start.col + (TSHAPE_SIZE - 1) >= b->colSize || ship.start.row + (TSHAPE_SIZE - 1) >= b->rowSize){
            return false;
        }

        if(ship.isHorizontal){
            for(int i=0;i < ship.length; i++){
                if(b->board[ship.start.row][ship.start.col + i] != -1 && (ship.start.col + i) < b->colSize){
                    return false;
                }
            }
            int mid = ship.start.col + 1;
            for(int i=0;i < ship.length;i++){
                if(b->board[ship.start.row + i][mid] != -1 && (ship.start.row + i) < b->rowSize){
                    return false;
                }
            }
        }

        if(ship.isHorizontal == false){
            for(int i=0;i < ship.length; i++){
                if(b->board[ship.start.row + i][ship.start.col] != -1 && (ship.start.row + i) < b->rowSize){
                    return false;
                }
            }
            int mid = ship.start.row + 1;
            for(int i=0;i < ship.length;i++){
                if(b->board[mid][ship.start.col + i] != -1 && (ship.start.col + i) < b->colSize){
                    return false;
                }
            }
        }

        return true;
    }

    for(int i = 0; i < ship.length; i++){
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
        return false;
    }

    if(ship.type == TSHAPE){
        if(ship.isHorizontal){
            for(int i=0;i<ship.length;i++){
                b->board[ship.start.row][ship.start.col + i] = ship.type;
            }
            int mid = ship.start.col + 1;
            for(int i=0;i<ship.length;i++){
                b->board[ship.start.row + i][mid] = ship.type;
            }
        }else{
            for(int i=0;i<ship.length;i++){
                b->board[ship.start.row + i][ship.start.col] = ship.type;
            }
            int mid = ship.start.row + 1;
            for(int i=0;i<ship.length;i++){
                b->board[mid][ship.start.col + i] = ship.type;
            }
        }
        return true;
    }

    if(ship.isHorizontal){ //horizontal
        for(int i=0;i<ship.length;i++){
            b->board[ship.start.row][ship.start.col + i] = ship.type;
        }
        b->lstOfShips = newShip(b->lstOfShips, ship);
    }else{//vertical
        for(int j=0;j<ship.length;j++){
            b->board[ship.start.row + j][ship.start.col] = ship.type;
        }
        b->lstOfShips = newShip(b->lstOfShips, ship);
    }
    return true;
}

int isAWaterShot(Board* b, Coordinate t){
    if(b->board[t.row][t.col] != -1){
        return b->board[t.row][t.col];
    }
    return -1;
}

void shoot(Board *b, Coordinate shot, int turn){
    Ships* s;
    if(isAWaterShot(b, shot) == -1){
        printf("Is a water shot!!\n");
        b->shotsFierd = newShot(b->shotsFierd,shot,false);
    }else{
        printf("Is NOT a water shot!!\n");
        b->board[shot.row][shot.col]=GOODSHOT;
        b->shotsFierd = newShot(b->shotsFierd,shot,true);
        s = searchLivingShips(b->lstOfShips, b->board[shot.row][shot.col]);
        if(s != NULL){
            if(s->ship.type == TSHAPE){
                if(s->ship.shotsRecived == s->ship.length + 2){
                    s->ship.isAlive = false;
                    s->ship.shotsRecived++;
                }else{
                    s->ship.shotsRecived++;
                }
            }else{
                if(s->ship.shotsRecived == s->ship.length + 1){
                    s->ship.isAlive = false;
                    s->ship.shotsRecived++;
                }else{
                    s->ship.shotsRecived++;
                }
            }
        }
    }
}

bool verifyendgame(){
	if(turn1 == WIN || turn2 == WIN)
		return true;
	else
		return false;
}

void printBoard(Board *b , Board *adv){
	for(int i=0;i<b->rowSize;i++){
		if(i <= 9){
            printf(KNRM "\t %d|",i);
        }else{
            printf(KNRM "\t%d|",i);
        }

		for(int j=0;j<b->colSize;j++){
            switch(b->board[i][j]){
                case -1:
                    if(j <= 9){
                        printf(KBLU "  ~  |");
                    }else{
                        printf(KBLU "  ~  |");
                    }
                    break;
                case GOODSHOT:
                    printf(KYEL "  X  ");
                    printf(KBLU "|");
                    break;
                case CARRIER:
                    printf(KCYN "  C  ");
                    printf(KBLU "|");
                    break;
                case BATTLESHIP:
                    printf(KCYN "  B  ");
                    printf(KBLU "|");
                    break;
                case CRUISER:
                    printf(KCYN "  R  ");
                    printf(KBLU "|");
                    break;
                case SUBMARINE:
                    printf(KCYN "  S  ");
                    printf(KBLU "|");
                    break;
                case DESTROYER:
                    printf(KCYN "  D  ");
                    printf(KBLU "|");
                    break;
                case TSHAPE:
                    printf(KCYN "  T  ");
                    printf(KBLU "|");
                    break;
            }
        }
		printf("\n");
	}

	printf("\t   ");
	for(int k=0;k<b->colSize;k++){
		if(k <=9){
            printf(KNRM "  %d  |",k);
        }else{
            printf(KNRM "  %d |",k);
        }
	}
	printf("\n\n");

    Shots* s;
    printf(KMAG "Shots fired: ");
    for(s = adv->shotsFierd; s != NULL; s = s->next){
        if(s->isHit){
            printf(KGRN "(%d,%d) ",s->target.row,s->target.col);
        }else{
            printf(KRED "(%d,%d) ",s->target.row,s->target.col);
        }
    }
    printf(KNRM "\n");
}


void randomPlaceShips(Board *b){
    Ship s1,s2,s3,s4,s5,s6;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    bool isNotOnBoard = true;

    s1.isAlive = true;
    s1.length = CARRIER_SIZE;
    s1.type = CARRIER;
    s1.shotsRecived = 0;
    while(isNotOnBoard){
        s1.start.row = (rand() % (b->rowSize - CARRIER_SIZE + 1));
        s1.start.col = (rand() % (b->colSize - CARRIER_SIZE + 1));
        s1.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s1);
        if(aux == true){
            isNotOnBoard = false;
        }
    }

    isNotOnBoard = true;
    s2.isAlive = true;
    s2.length = BATTLESHIP_SIZE;
    s2.type = BATTLESHIP;
    s2.shotsRecived = 0;
    while(isNotOnBoard){
        s2.start.row = (rand() % (b->rowSize - BATTLESHIP_SIZE + 1));
        s2.start.col = (rand() % (b->colSize - BATTLESHIP_SIZE + 1));
        s2.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s2);
        if(aux == true){
            isNotOnBoard = false;
        }
    }

    isNotOnBoard = true;
    s3.isAlive = true;
    s3.length = CRUSIER_SIZE;
    s3.type = CRUISER;
    s3.shotsRecived = 0;
    while(isNotOnBoard){
        s3.start.row = (rand() % (b->rowSize - CRUSIER_SIZE + 1));
        s3.start.col = (rand() % (b->colSize - CRUSIER_SIZE + 1));
        s3.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s3);
        if(aux == true){
            isNotOnBoard = false;
        }

    }

    isNotOnBoard = true;
    s4.isAlive = true;
    s4.length = SUBMARINE_SIZE;
    s4.type = SUBMARINE;
    s4.shotsRecived = 0;
    while(isNotOnBoard){
        s4.start.row = (rand() % (b->rowSize - SUBMARINE_SIZE + 1));
        s4.start.col = (rand() % (b->colSize - SUBMARINE_SIZE + 1));
        s4.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s4);
        if(aux == true){
            isNotOnBoard = false;
        }
    }

    isNotOnBoard = true;
    s5.isAlive = true;
    s5.length = DESTROYER_SIZE;
    s5.type = DESTROYER;
    s5.shotsRecived = 0;
    while(isNotOnBoard){
        s5.start.row = (rand() % (b->rowSize - DESTROYER_SIZE + 1));
        s5.start.col = (rand() % (b->colSize - DESTROYER_SIZE + 1));
        s5.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b,s5);
        if(aux == true){
            isNotOnBoard = false;
        }
    }

    isNotOnBoard = true;
    s6.isAlive = true;
    s6.length = TSHAPE_SIZE;
    s6.type = TSHAPE;
    s6.shotsRecived = 0;
    while(isNotOnBoard){
        s6.start.row = (rand() % (b->rowSize - TSHAPE_SIZE + 1));
        s6.start.col = (rand() % (b->colSize - DESTROYER_SIZE + 1));
        s6.isHorizontal = (rand() % 2);
        bool aux = setShipPos(b, s6);
        if(aux == true){
            isNotOnBoard = false;
        }
    }
}