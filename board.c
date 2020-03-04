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
    b->curQtdShips = 0;
    b->shotsFierd = NULL;
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

    if(ship.isHorizontal){ //horizontal
        for(int i=0;i<ship.length;i++){
            b->board[ship.start.row][ship.start.col + i] = ship.type;
        }
        b->ships[b->curQtdShips] = ship;
        b->curQtdShips++;
    }else{//vertical
        for(int j=0;j<ship.length;j++){
            b->board[ship.start.row + j][ship.start.col] = ship.type;
        }
        b->ships[b->curQtdShips] = ship;
        b->curQtdShips++;
    }
    return true;
}

bool isAWaterShot(Board* b, Coordinate t){
    Ship s;
    for(int i=0;i<b->curQtdShips;i++){
        s = b->ships[i];
        if(s.isAlive){
            if(s.isHorizontal){
                for(int j=s.start.col;j<s.length;j++){
                    printf("H j: %d\n",j);
                    if(j == t.col && s.start.row == t.row){
                        printf("Ship: %d\n",s.type);
                        printf("coords: (%d,%d)\n",t.col,t.row);
                        return false;
                    }
                }
            }else{
                printf("start: (%d,%d)\n",s.start.col,s.start.row);
                printf("length: %d\n",s.length);
                for(int j=s.start.row;j<=s.length;j++){
                    // printf("notH j: %d\n",j);
                    printf("coords: (%d,%d)\n",t.col,j);
                    if(j == t.row && t.col == s.start.col){
                        // printf("coords: (%d,%d)\n",t.col,t.row);
                        return false;
                    }
                }
            }
        }
        printf("\n");
    }
    return true;
}

void shoot(Board *b, Coordinate shot, int turn){
	if(shot.row < 0 || shot.col < 0){
        printf(KRED "That is an invalid Coordinate, please respect the board edges.\n" KNRM);
        return;
    }else if(shot.row >= b->rowSize || shot.col >= b->colSize){
        printf(KRED "That is an invalid Coordinate, please respect the board edges.\n" KNRM);
        return;
    }

    b->shotsFierd = newShot(b->shotsFierd,shot);
    if(isAWaterShot(b, shot)){
        printf("Is a water shot!!\n");
    }else{
        printf("Is NOT a water shot!!\n");
    }

}

void printBoard(Board *b){
	for(int i=0;i<b->rowSize;i++){
		printf(KNRM "\t%d|",i);
		for(int j=0;j<b->colSize;j++){
            switch(b->board[i][j]){
                case -1:
                    printf(KBLU " ~ |"); 
                    break;
                case 5:
                    printf(KRED " ⊗ ");
                    printf(KBLU "|");
                    break;
                case 6:
                    printf(KYEL " X ");
                    printf(KBLU "|");
                    break;
                case 0:
                    printf(KCYN " C ");
                    printf(KBLU "|");
                    break;
                case 1:
                    printf(KCYN " B ");
                    printf(KBLU "|");
                    break;
                case 2:
                    printf(KCYN " R ");
                    printf(KBLU "|");
                    break;
                case 3:
                    printf(KCYN " S ");
                    printf(KBLU "|");
                    break;
                case 4:
                    printf(KCYN " D ");
                    printf(KBLU "|");
                    break;
            }
        }
		printf("\n");
	}

	printf("\t   ");
	for(int k=0;k<b->colSize;k++){
		printf(KNRM "%d | ",k);
	}
	printf("\n\n");
    
    Shots* s;
    for(s = b->shotsFierd; s != NULL; s = s->next){
        printf(KMAG "(%d,%d) ",s->target.col,s->target.row);
    }
    printf(KNRM "\n");
}


void randomPlaceShips(Board *b){
    Ship s1,s2,s3,s4,s5,s;
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
}

Shots* newShot(Shots* lst, Coordinate s){
    Shots* node = (Shots*)malloc(sizeof(Shots));
    if(node != NULL){
        node->next = lst;
        node->target.row = s.row;
        node->target.col = s.col;
    }
    return node;
}

Shots* searchShot(Shots* lst, Coordinate k){
    Shots* p;
    for(p=lst; p!=NULL; p = p->next){
        if(p->target.row == k.row && p->target.col == k.col){
            return p;
        }
    }
    return NULL;
}

void delAllShots(Shots *lst){
    Shots* s = lst, *aux;
    while(s != NULL){
        aux = s->next;
        free(s);
        s = aux;
    }
}

void printShots(Shots* lst){
    Shots* aux = lst;
    while(aux != NULL){
        printf(KMAG "\n(%d,%d)\n" KNRM, aux->target.row,aux->target.col);
        aux = aux->next;
    }
}