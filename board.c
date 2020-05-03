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
                case WATERSHOT:
                    printf(KRED "  X  ");
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
}

void printAllShipsTypes(){

    printf("Name: Carrier: \t Battleship: \t Cruiser:\tSubmarine:\tDestroyer:\tTShape: \n");
    // printf("Size:    5  \t     4  \t    3  \t\t   3  \t\t    3  \t\t   5  \n");
    printf("Code:    %d  \t     %d  \t    %d \t\t   %d \t\t    %d \t\t   %d\n\n",CARRIER,BATTLESHIP,CRUISER,SUBMARINE,DESTROYER,TSHAPE);
    printf("\t " KCYN "C\t     B\t\t    R\t\t   S\t\t    D\t\t" KRED " T " KCYN "T T\n");
    printf("\t " KCYN "C\t     B\t\t    R\t\t   S\t\t    D\t\t   T  \n");
    printf("\t " KCYN "C\t     B\t\t    R\t\t   S\t\t     \t\t   T \n");
    printf("\t " KCYN "C\t     B\t\t     \t\t    \t\t     \t\t     \n");
    printf("\t " KCYN "C\t      \t\t     \t\t    \t\t     \t\t     \n");
}

int* selectShips(int row, int col){
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
    if(ship.start.col < 0 || ship.start.row < 0 || ship.start.row >= b->rowSize || ship.start.col >= b->colSize){
        return false;
    }

    if(ship.rotation != ROTATION_0 && ship.rotation != ROTATION_180 && ship.rotation != ROTATION_270 && ship.rotation != ROTATION_90)
        return false;

    if(ship.type == TSHAPE){
        int mid;
        if(ship.start.col + (TSHAPE_SIZE - 1) >= b->colSize || ship.start.row + (TSHAPE_SIZE - 1) >= b->rowSize){
            return false;
        }

        switch (ship.rotation)
        {
        case ROTATION_0:
            for(int i=0;i < ship.length; i++){
                if(b->board[ship.start.row][ship.start.col + i].shipType != -1 && (ship.start.col + i) < b->colSize){
                    return false;
                }
            }
            mid = ship.start.col + 1;
            for(int i=0;i < ship.length;i++){
                if(b->board[ship.start.row + i][mid].shipType!= -1 && (ship.start.row + i) < b->rowSize){
                    return false;
                }
            }
            break;
        case ROTATION_90:
            for(int i=0;i<ship.length;i++){
                if(ship.start.row - i < 0)
                    return false;
                if(b->board[ship.start.row - i][ship.start.col].shipType != -1)
                    return false;
            }
            mid = ship.start.row - 1;
            for(int i=0;i<ship.length;i++){
                if(ship.start.col - i < 0)
                    return false;
                if(b->board[mid][ship.start.col - i].shipType != -1)
                    return false;
            }
        break;
        case ROTATION_180:
            for(int i=0;i < ship.length;i++){
                if(ship.start.col - i < 0)
                    return false;
                if(b->board[ship.start.row][ship.start.col - i].shipType != -1)
                    return false;
            }
            mid = ship.start.col - 1;
            for(int i=0;i < ship.length; i++){
                if(ship.start.row - i< 0)
                    return false;
                if(b->board[ship.start.row - i][mid].shipType != -1)
                    return false;
            }
            break;
        case ROTATION_270:
            for(int i=0;i < ship.length; i++){
                if(b->board[ship.start.row + i][ship.start.col].shipType != -1 && (ship.start.row + i) < b->rowSize){
                    return false;
                }
            }
            mid = ship.start.row + 1;
            for(int i=0;i < ship.length;i++){
                if(b->board[mid][ship.start.col + i].shipType != -1 && (ship.start.col + i) < b->colSize){
                    return false;
                }
            }
            break;
        }
    }

    switch (ship.rotation){
    case ROTATION_0:
        if(ship.start.col + ship.length > b->colSize)
            return false;
        for(int i=0;i<ship.length;i++){
            if(b->board[ship.start.row][ship.start.col + i].shipType != -1)
                return false;
        }
        break;
    case ROTATION_180:
        if(ship.start.col - ship.length < -1)
            return false;
        for(int i=0;i<ship.length;i++){
            if(b->board[ship.start.row][ship.start.col - i].shipType != -1)
                return false;
        }
        break;
    case ROTATION_90:
        if(ship.start.row - ship.length < -1)
            return false;
        for(int i=0;i<ship.length;i++){
            if(b->board[ship.start.row - i][ship.start.col].shipType != -1)
                return false;
        }
        break;
    case ROTATION_270:
        if(ship.start.row + ship.length > b->rowSize)
            return false;

        for(int i=0;i<ship.length;i++){
            if(b->board[ship.start.row + i][ship.start.col].shipType != -1){
                return false;
            }
        }
        break;
    }

    return true;
}

bool setShip(Board *b, Ship ship){
    if(!isValidPos(b,ship)){
        return false;
    }

    if(ship.type == TSHAPE){
        int mid;
        switch (ship.rotation)
        {
        case ROTATION_0:
            for(int i=0;i<ship.length;i++){
                b->board[ship.start.row][ship.start.col + i].shipType = ship.type;
                b->board[ship.start.row][ship.start.col + i].hasShip = true;
            }
            mid = ship.start.col + 1;
            for(int i=0;i<ship.length;i++){
                b->board[ship.start.row + i][mid].shipType = ship.type;
                b->board[ship.start.row + i][mid].hasShip = true;
            }
            break;
        case ROTATION_90:
            for(int i=0;i<ship.length;i++){
                b->board[ship.start.row - i][ship.start.col].shipType = ship.type;
                b->board[ship.start.row - i][ship.start.col].hasShip = true;
            }
            mid = ship.start.row - 1;
            for(int i=0;i<ship.length;i++){
                b->board[mid][ship.start.col - i].shipType = ship.type;
                b->board[mid][ship.start.col - i].hasShip = true;
            }
            break;
        case ROTATION_180:
            for(int i=0;i < ship.length;i++){
                b->board[ship.start.row][ship.start.col - i].shipType = ship.type;
                b->board[ship.start.row][ship.start.col - i].hasShip = true;
            }
            mid = ship.start.col - 1;
            for(int i=0;i < ship.length; i++){
                b->board[ship.start.row - i][mid].shipType = ship.type;
                b->board[ship.start.row - i][mid].hasShip = true;
            }
            break;
        case ROTATION_270:
            for(int i=0;i<ship.length;i++){
                b->board[ship.start.row + i][ship.start.col].shipType = ship.type;
                b->board[ship.start.row + i][ship.start.col].hasShip = true;
            }
            mid = ship.start.row + 1;
            for(int i=0;i<ship.length;i++){
                b->board[mid][ship.start.col + i].shipType = ship.type;
                b->board[mid][ship.start.col + i].hasShip = true;
            }
            break;
        }
        return true;
    }


    switch (ship.rotation)
    {
    case ROTATION_0:
        for(int i=0;i<ship.length;i++){
            b->board[ship.start.row][ship.start.col + i].shipType = ship.type;
            b->board[ship.start.row][ship.start.col + i].hasShip = true;
        }
        break;
    case ROTATION_270:
        for(int j=0;j<ship.length;j++){
            b->board[ship.start.row + j][ship.start.col].shipType = ship.type;
            b->board[ship.start.row + j][ship.start.col].hasShip = true;
        }
        break;
    case ROTATION_180:
        for(int i=0;i<ship.length;i++){
            b->board[ship.start.row][ship.start.col - i].shipType = ship.type;
            b->board[ship.start.row][ship.start.col - i].hasShip = true;
        }
        break;
    case ROTATION_90:
        for(int j=0;j<ship.length;j++){
            b->board[ship.start.row - j][ship.start.col].shipType = ship.type;
            b->board[ship.start.row - j][ship.start.col].hasShip = true;
        }
        break;
    }
    return true;
}

void randomPlaceShips(Board *b, int* lstOfShips){
    Ship s;
    Coordinate c;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    bool isNotOnBoard = true;


    for(int i=0;i<6;i++){
        switch (i)
        {
        case CARRIER:
            for(int k=0;k<lstOfShips[i];k++){
                s.length = CARRIER_SIZE;
                s.type = CARRIER;
                while(isNotOnBoard){
                    s.rotation = (rand() % 4);
                    s.start.row = (rand() % (b->rowSize - CARRIER_SIZE + 1));
                    s.start.col = (rand() % (b->colSize - CARRIER_SIZE + 1));
                    if(setShip(b,s)){
                        isNotOnBoard = false;
                    }
                }
                isNotOnBoard = true;
            }
            break;
        case BATTLESHIP:
            for(int k=0;k<lstOfShips[i];k++){
                s.length = BATTLESHIP_SIZE;
                s.type = BATTLESHIP;
                while(isNotOnBoard){
                    s.rotation = (rand() % 4);
                    s.start.row = (rand() % (b->rowSize - BATTLESHIP_SIZE + 1));
                    s.start.col = (rand() % (b->colSize - BATTLESHIP_SIZE + 1));
                    if(setShip(b,s)){
                        isNotOnBoard = false;
                    }
                }
                isNotOnBoard = true;
            }
            break;
        case CRUISER:
            for(int k=0;k<lstOfShips[i];k++){
                s.length = CRUSIER_SIZE;
                s.type = CRUISER;
                while(isNotOnBoard){
                    s.rotation = (rand() % 4);
                    s.start.row = (rand() % (b->rowSize - CRUSIER_SIZE + 1));
                    s.start.col = (rand() % (b->colSize - CRUSIER_SIZE + 1));
                    if(setShip(b,s)){
                        isNotOnBoard = false;
                    }
                }
                isNotOnBoard = true;
            }
            break;
        case SUBMARINE:
            for(int k=0;k<lstOfShips[i];k++){
                s.length = SUBMARINE_SIZE;
                s.type = SUBMARINE;
                while(isNotOnBoard){
                    s.rotation = (rand() % 4);
                    s.start.row = (rand() % (b->rowSize - SUBMARINE_SIZE + 1));
                    s.start.col = (rand() % (b->colSize - SUBMARINE_SIZE + 1));
                    if(setShip(b,s)){
                        isNotOnBoard = false;
                    }
                }
                isNotOnBoard = true;
            }
            break;
        case DESTROYER:
            for(int k=0;k<lstOfShips[i];k++){
                s.length = DESTROYER_SIZE;
                s.type = DESTROYER;
                while(isNotOnBoard){
                    s.rotation = (rand() % 4);
                    s.start.row = (rand() % (b->rowSize - DESTROYER_SIZE + 1));
                    s.start.col = (rand() % (b->colSize - DESTROYER_SIZE + 1));
                    if(setShip(b,s)){
                        isNotOnBoard = false;
                    }
                }
                isNotOnBoard = true;
            }
            break;
        case TSHAPE:
            for(int k=0;k<lstOfShips[i];k++){
                s.length = TSHAPE_SIZE;
                s.type = TSHAPE;
                while(isNotOnBoard){
                    s.rotation = (rand() % 4);
                    s.start.row = (rand() % (b->rowSize - TSHAPE_SIZE + 1));
                    s.start.col = (rand() % (b->colSize - DESTROYER_SIZE + 1));
                    if(setShip(b,s)){
                        isNotOnBoard = false;
                    }
                }
                isNotOnBoard = true;
            }
            break;
        }
    }
}

void manualyPlanceShips(Board* b, int* lstOfShips){

	Ship s;
    Coordinate c;
    int r,col,rot;
	for(int i=0 ; i < 6 ; i++){
		switch(i){
			case CARRIER:
				for(int k=0;k<lstOfShips[i];k++){
                    s.length = CARRIER_SIZE;
                    s.type = CARRIER;
                    clearScreen();
                    printAllShipsTypes();
                    printWarningMsg("Specify the initial coordinates(row,col) of Carrier ship and your rotation. (eg 5 5 90)");
                    scanf("%d %d %d",&r,&col,&rot);
                    s.start.row = r;
                    s.start.col = col;
                    s.rotation = convertRotation(rot);
                    while(setShip(b,s) == false){
                        clearScreen();
                        printAllShipsTypes();
                        printErrorMsg("Wrong coordinates or rotation. Pay attention to the dimensions of the board.");
                        printWarningMsg("Please specify news coordinates(row,col) of Carrier ship and your rotation. (eg 5 5 90)");
                        scanf("%d %d %d",&r,&col,&rot);
                        s.start.row = r;
                        s.start.col = col;
                        s.rotation = convertRotation(rot);
                    }
                printBoard(b);
                }
			break;
			case BATTLESHIP:
				for(int k=0;k<lstOfShips[i];k++){
                    s.length = BATTLESHIP_SIZE;
                    s.type = BATTLESHIP;
                    printAllShipsTypes();
                    printWarningMsg("Specify the initial coordinates(row,col) of Battleship ship and your rotation. (eg 5 5 90)");
                    scanf("%d %d %d",&r,&col,&rot);
                    s.start.row = r;
                    s.start.col = col;
                    s.rotation = convertRotation(rot);
                    while(setShip(b,s) == false){
                        clearScreen();
                        printAllShipsTypes();
                        printErrorMsg("Wrong coordinates or rotation. Pay attention to the dimensions of the board.");
                        printWarningMsg("Please specify news coordinates(row,col) of Battleship ship and your rotation. (eg 5 5 90)");
                        scanf("%d %d %d",&r,&col,&rot);
                        s.start.row = r;
                        s.start.col = col;
                        s.rotation = convertRotation(rot);
                    }
                    printBoard(b);
                }
			break;
			case CRUISER:
				for(int k=0;k<lstOfShips[i];k++){
                    s.length = CRUSIER_SIZE;
                    s.type = CRUISER;
                    printAllShipsTypes();
                    printWarningMsg("Specify the initial coordinates(row,col) of Cruiser ship and your rotation. (eg 5 5 90)");
                    scanf("%d %d %d",&r,&col,&rot);
                    s.start.row = r;
                    s.start.col = col;
                    s.rotation = convertRotation(rot);
                    while(setShip(b,s) == false){
                        clearScreen();
                        printAllShipsTypes();
                        printErrorMsg("Wrong coordinates or rotation. Pay attention to the dimensions of the board.");
                        printWarningMsg("Please specify news coordinates(row,col) of Cruiser ship and your rotation. (eg 5 5 90)");
                        scanf("%d %d %d",&r,&col,&rot);
                        s.start.row = r;
                        s.start.col = col;
                        s.rotation = convertRotation(rot);
                    }
                    printBoard(b);
                }
			break;
			case SUBMARINE:
				for(int k=0;k<lstOfShips[i];k++){
                    s.length = SUBMARINE_SIZE;
                    s.type = SUBMARINE;
                    printWarningMsg("Specify the initial coordinates(row,col) of Submarine ship and your rotation. (eg 5 5 90)");
                    scanf("%d %d %d",&r,&col,&rot);
                    s.start.row = r;
                    s.start.col = col;
                    s.rotation = convertRotation(rot);
                    while(setShip(b,s) == false){
                        clearScreen();
                        printAllShipsTypes();
                        printErrorMsg("Wrong coordinates or rotation. Pay attention to the dimensions of the board.");
                        printWarningMsg("Please specify news coordinates(row,col) of Submarine ship and your rotation. (eg 5 5 90)");
                        scanf("%d %d %d",&r,&col,&rot);
                        s.start.row = r;
                        s.start.col = col;
                        s.rotation = convertRotation(rot);
                    }
                    printBoard(b);
                }
			break;
			case DESTROYER:
				for(int k=0;k<lstOfShips[i];k++){
                    s.length = DESTROYER_SIZE;
                    s.type = DESTROYER;
                    printAllShipsTypes();
                    printWarningMsg("Specify the initial coordinates(row,col) of Destroyer ship and your rotation. (eg 5 5 90)");
                    scanf("%d %d %d",&r,&col,&rot);
                    s.start.row = r;
                    s.start.col = col;
                    s.rotation = convertRotation(rot);
                    while(setShip(b,s) == false){
                        clearScreen();
                        printAllShipsTypes();
                        printErrorMsg("Wrong coordinates or rotation. Pay attention to the dimensions of the board.");
                        printWarningMsg("Please specify news coordinates(row,col) of Destroyer ship and your rotation. (eg 5 5 90)");
                        scanf("%d %d %d", &r, &col, &rot);
                        s.start.row = r ;
                        s.start.col = col ;
                        s.rotation = convertRotation(rot);
                    }
                    printBoard(b);
                }
			break;
			case TSHAPE:
        for(int k=0;k<lstOfShips[i];k++){
            s.length = TSHAPE_SIZE;
            s.type = TSHAPE;
            printAllShipsTypes();
            printWarningMsg("Specify the initial coordinates(row,col) of Tshape ship and your rotation. (eg 5 5 90)");
            scanf("%d %d %d",&r,&col,&rot);
            s.start.row = r;
            s.start.col = col;
            s.rotation = convertRotation(rot);
            while(setShip(b,s) == false){
                clearScreen();
                printAllShipsTypes();
                printErrorMsg("Wrong coordinates or rotation. Pay attention to the dimensions of the board.");
                printWarningMsg("Please specify news coordinates(row,col) of Tshape ship and your rotation. (eg 5 5 90)");
                scanf("%d %d %d", &r, &col, &rot);
                s.start.row = r ;
                s.start.col = col ;
                s.rotation = convertRotation(rot);
            }
            printBoard(b);
        }
			break;
		}
	}
}


int convertRotation(int rot){
	if(rot == 0){
		return ROTATION_0;
	}
	if(rot == 90){
		return ROTATION_90;
	}
	if(rot == 180){
		return ROTATION_180;
	}
	if(rot == 270){
		return ROTATION_270;
	}
    return -1;
}

void fire(Board* p1board, Board* p2board){
	int tmp=0;
	int turn=1;
	Coordinate shot;
	int r,c;

	while(tmp != 1){
		if(turn == 1){
            clearScreen();
            printWarningMsg("\t\t\t\t\t\t\t#### Board Player 1 ###\n\n");
            printBoard(p1board);
			printWarningMsg("\n\nPlayer 1 is your turn!\n");
            printWarningMsg("Specify the coordinates of your shots:");
			for(int i=0;i<3;i++){
				printWarningMsgInt("Shot" ,i+1);
				scanf("%d %d",&r,&c);
				shot.row=r;
				shot.col=c;
				while(r<0 || c<0 ||  r>p1board->rowSize || c >= p1board->colSize){
					printErrorMsg("That is an invalid Coordinate, please respect the board edges.");
					printWarningMsg("Player 1 introduce one shot coordinates (R C):\n");
					printWarningMsgInt("Shot",i+1);
					scanf("%d %d",&r,&c);
                    shot.row=r;
                    shot.col=c;
				}
        while(p2board->board[r][c].wasHit == true){
            printErrorMsg("Coordinate already been used, please enter a new coordinate.");
            printWarningMsg("Player 1 introduce one shot coordinates (R C):\n");
            printWarningMsgInt("Shot" ,i+1);
            scanf("%d %d",&r,&c);
            shot.row=r;
            shot.col=c;
        }
        if(p2board->board[r][c].shipType != -1 && p2board->board[r][c].wasHit == false){
            p1board->shotsFierd = newShot(p1board->shotsFierd,shot,true);
            p2board-> hp-- ;
            p2board->board[r][c].wasHit = true;
            p2board->board[r][c].shipType = GOODSHOT;
            if(p2board->hp == 0){
                printSuccessMsg("Congratulations , Player 1 won! ");
                exit(0);
            }
            printShots(p1board->shotsFierd);
        }else{
            p1board->shotsFierd = newShot(p1board->shotsFierd,shot,false);
            p2board->board[r][c].shipType = WATERSHOT;
            p2board->board[r][c].wasHit = true;
            printShots(p1board->shotsFierd);
        }
			}
			turn=2;
        }

    if(turn == 2){
        clearScreen();
        printWarningMsg("\t\t\t\t\t\t\t#### Board Player 2 ###\n\n");
        printBoard(p2board);
        printWarningMsg("\n\nPlayer 2 is your turn!");
        printWarningMsg("Specify the coordinates of your shots:");
        for(int i=0;i<3;i++){
            printWarningMsgInt("Shot" ,i+1);
            scanf("%d %d",&r,&c);
            shot.row=r;
            shot.col=c;
            while(r<0 || c<0 ||  r>p2board->rowSize || c >= p2board->colSize ){
                printErrorMsg("That is an invalid Coordinate, please respect the board edges.");
                printWarningMsg("Player 2 introduce one shot coordinates (R C):\n");
                printWarningMsgInt("Shot" ,i+1);
                scanf("%d %d",&r,&c);
            shot.row=r;
            shot.col=c;
        }
        while(p1board->board[r][c].wasHit == true){
            printErrorMsg("Coordinate already been used, please enter a new coordinate.");
            printWarningMsg("Player 2 introduce one shot coordinates (R C):\n");
            printWarningMsgInt("Shot" ,i+1);
            scanf("%d %d",&r,&c);
            shot.row=r;
            shot.col=c;
        }
        if(p1board->board[r][c].shipType != -1 && p1board->board[r][c].wasHit == false){
            p2board->shotsFierd = newShot(p2board->shotsFierd,shot,true);
            p1board-> hp-- ;
            p1board->board[r][c].shipType = 6;
            p1board->board[r][c].wasHit = true;
            if(p1board->hp == 0){
                printSuccessMsg("Congratulations , Player 2 won! ");
                exit(0);
            }
            printShots(p2board->shotsFierd);
        }else{
            p2board->shotsFierd = newShot(p2board->shotsFierd,shot,true);
            p1board->board[r][c].shipType = WATERSHOT;
            p1board->board[r][c].wasHit = true;
            printShots(p2board->shotsFierd);
        }

        }
            turn=1;
        }
    }
}

Shots* newShot(Shots* lst, Coordinate s, bool isHit){
    Shots* node = (Shots*)malloc(sizeof(Shots));
    if(node != NULL){
        node->next = lst;
        node->target.row = s.row;
        node->target.col = s.col;
        node->isHit=isHit;
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

void clearShots(Shots *lst){
    Shots* s = lst, *aux;
    while(s != NULL){
        aux = s->next;
        free(s);
        s = aux;
    }
}

void printShots(Shots* lst){
    Shots* s;
    printf(KMAG "Shots fired: ");
    for(s = lst; s != NULL; s = s->next){
        if(s->isHit){
            printf(KGRN "(%d,%d) ",s->target.row,s->target.col);
        }else{
            printf(KRED "(%d,%d) ",s->target.row,s->target.col);
        }
    }
    printf(KNRM "\n");
}