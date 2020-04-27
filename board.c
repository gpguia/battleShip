#include "board.h"


void newBoard(int row, int col, Board* p1, Board* p2){
    int ok = -1;

	while(row < 20 || col > 40 || row < 20 || col > 40){
		printWarningMsg("Incorrect sizes (Minimum size:20x20 ; Maximum size:40x40)");
		printSuccessMsg("Introduce new format:");
		scanf("%d%d",&row,&col);
	}

    
    
    p1->rowSize = row;
    p1->colSize = col;
    p1->board = (Cell **)malloc(row * sizeof(Cell*));
    p1->hp = 0;

    p2->rowSize = row;
    p2->colSize = col;
    p2->board = (Cell **)malloc(row * sizeof(Cell*));
    p2->hp = 0;

    for(int i = 0; i < row; i++) {
        p1->board[i] = (Cell *)malloc(col * sizeof(Cell));
        p2->board[i] = (Cell *)malloc(col * sizeof(Cell));
    }
    for(int i=0; i<row; i++){
        for(int j=0;j<col; j++){
            p1->board[i][j].hasShip = false;
            p1->board[i][j].wasHit = false;
            p1->board[i][j].shipType = -1;
            
            p2->board[i][j].hasShip = false;
            p2->board[i][j].wasHit = false;
            p2->board[i][j].shipType = -1;
        }
    }
    p1->shotsFierd = NULL;
    p2->shotsFierd = NULL;
}

void setHP(Board* p1, Board* p2, int* lstOfShips){
    for(int i=0;i<6;i++){
        switch (i)
        {
        case CARRIER:
            p1->hp += CARRIER_SIZE * lstOfShips[i];
            p2->hp += CARRIER_SIZE * lstOfShips[i];
            break;
        case BATTLESHIP:
            p1->hp += BATTLESHIP_SIZE * lstOfShips[i];
            p2->hp += BATTLESHIP_SIZE * lstOfShips[i];
            break;
        case CRUISER:
            p1->hp += CRUSIER_SIZE * lstOfShips[i];
            p2->hp += CRUSIER_SIZE * lstOfShips[i];
            break;
        case SUBMARINE:
            p1->hp += SUBMARINE_SIZE * lstOfShips[i];
            p2->hp += SUBMARINE_SIZE * lstOfShips[i];
            break;
        case DESTROYER:
            p1->hp += DESTROYER_SIZE * lstOfShips[i];
            p2->hp += DESTROYER_SIZE * lstOfShips[i];
            break;
        case TSHAPE:
            p1->hp += (TSHAPE_SIZE + 2) * lstOfShips[i];
            p2->hp += (TSHAPE_SIZE + 2) * lstOfShips[i];
            break;
        }
    }
}

void printBoard(Board *b){
    for(int i=0 ;i < b->rowSize; i++){
		if(i <= 9){
            printf(KNRM "\t %d|",i);
        }else{
            printf(KNRM "\t%d|",i);
        }

        for(int j=0; j<b->colSize;j++){
            switch(b->board[i][j].shipType){
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
    for(s = b->shotsFierd; s != NULL; s = s->next){
        if(s->isHit){
            printf(KGRN "(%d,%d) ",s->target.row,s->target.col);
        }else{
            printf(KRED "(%d,%d) ",s->target.row,s->target.col);
        }
    }
    printf(KNRM "\n");
}

void printAllShipsTypes(){

    printf("Name: Carrier: \t Battleship: \t Cruiser:\tSubmarine:\tDestroyer:\tTShape: \n");
    // printf("Size:    5  \t     4  \t    3  \t\t   3  \t\t    3  \t\t   5  \n");
    printf("Code:    %d  \t     %d  \t    %d \t\t   %d \t\t    %d \t\t   %d\n\n",CARRIER,BATTLESHIP,CRUISER,SUBMARINE,DESTROYER,TSHAPE);
    printf("\t " KCYN "C\t     B\t\t    R\t\t   S\t\t    D\t\t T T T\n");
    printf("\t " KCYN "C\t     B\t\t    R\t\t   S\t\t    D\t\t   T  \n");
    printf("\t " KCYN "C\t     B\t\t    R\t\t   S\t\t     \t\t   T \n");
    printf("\t " KCYN "C\t     B\t\t     \t\t    \t\t     \t\t     \n");
    printf("\t " KCYN "C\t      \t\t     \t\t    \t\t     \t\t     \n");
}

int* selectChips(int row, int col){
    clearScreen();

    int maxNumberOfShips = (row * col)/ 25;
    int numShips;
    printWarningMsgInt("Select how many ships you would like to have? Min: 6 MAX:",maxNumberOfShips);
    scanf("%d", &numShips);

    while(numShips > maxNumberOfShips || numShips < 6){
        printErrorMsgInt("Please insert a number between 6 and ",maxNumberOfShips);
        scanf("%d",&numShips);
    }
    int* lstOfShips = malloc(6 * sizeof(int));

    for(int i=0;i<MAXNUMSHIPS;i++){
        lstOfShips[i] = 1;
    }

    if(numShips == 6){
        return lstOfShips;
    }

    printWarningMsg("Now you will select the types of your ships, remember that you already have 1 of each type :)");
    printAllShipsTypes();
    int curQtdShips = 6;
    int code,qtd;
    while(curQtdShips < numShips){
        printWarningMsg("Insert the code of the ship and the quantity: (eg: 0 1)");
        scanf("%d%d",&code,&qtd);
        while(curQtdShips + qtd > numShips){
            printErrorMsgInt("Your max number of ships is: ",numShips);
            printErrorMsgInt("You can not add this ammount of ships, you already have: ",curQtdShips);
            printWarningMsg("Insert the code of the ship and the quantity: (eg: 0 1)");
            scanf("%d%d",&code,&qtd);
        }
        curQtdShips += qtd;
        lstOfShips[code] += qtd;
    }

    return lstOfShips;
}

bool isValidPos(Board* b, Ship ship){
    if(ship.start.col < 0 || ship.start.row < 0){
        return false;
    }

    if(ship.rotation == ROTATION_0 || ship.rotation == ROTATION_180){
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

        if(ship.rotation == ROTATION_0 || ship.rotation == ROTATION_180){
            for(int i=0;i < ship.length; i++){
                if(b->board[ship.start.row][ship.start.col + i].hasShip != -1 && (ship.start.col + i) < b->colSize){
                    return false;
                }
            }
            int mid = ship.start.col + 1;
            for(int i=0;i < ship.length;i++){
                if(b->board[ship.start.row + i][mid].shipType != -1 && (ship.start.row + i) < b->rowSize){
                    return false;
                }
            }
        }

        if(ship.rotation == ROTATION_270 || ship.rotation == ROTATION_90){
            for(int i=0;i < ship.length; i++){
                if(b->board[ship.start.row + i][ship.start.col].shipType != -1 && (ship.start.row + i) < b->rowSize){
                    return false;
                }
            }
            int mid = ship.start.row + 1;
            for(int i=0;i < ship.length;i++){
                if(b->board[mid][ship.start.col + i].shipType != -1 && (ship.start.col + i) < b->colSize){
                    return false;
                }
            }
        }

        return true;
    }

    for(int i = 0; i < ship.length; i++){
        if(ship.rotation == ROTATION_0 || ship.rotation == ROTATION_180){
            if(b->board[ship.start.row][ship.start.col + i].shipType != -1 && (ship.start.col + i) < b->colSize) // -1 is water
                return false;
        }else{//vertical
            if(b->board[ship.start.row + i][ship.start.col].shipType != -1 && (ship.start.row + i) < b->rowSize) // -1 is water
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
        //TODO check rotation...
    }

    if(ship.rotation == ROTATION_0 || ROTATION_180){ //horizontal
        for(int i=0;i<ship.length;i++){
            b->board[ship.start.row][ship.start.col + i].shipType = ship.type;
        }
    }else{//vertical
        for(int j=0;j<ship.length;j++){
            b->board[ship.start.row + j][ship.start.col].shipType = ship.type;
        }
    }
    return true;
}