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
    p1->board = (PiceBoard **)malloc(row * sizeof(PiceBoard*));

    p2->rowSize = row;
    p2->colSize = col;
    p2->board = (PiceBoard **)malloc(row * sizeof(PiceBoard*));

    for(int i = 0; i < row; i++) {
        p1->board[i] = (PiceBoard *)malloc(col * sizeof(PiceBoard));
        p2->board[i] = (PiceBoard *)malloc(col * sizeof(PiceBoard));
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

    printf("Name: Carrier: \t Battleship: \t Cruiser: \t Submarine: \t Destroyer: \t TShape: \n");
    printf("Size:    5  \t     4  \t    3  \t\t     3  \t     3  \t    5  \n");
    printf("Code:    %d  \t     %d  \t    %d \t\t     %d \t\t     %d \t\t    %d\n",CARRIER,BATTLESHIP,CRUISER,SUBMARINE,DESTROYER,TSHAPE);
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
        lstOfShips[i] = 0;
    }

    printWarningMsg("Now you will select the types of your ships :)");
    printAllShipsTypes();
    int curQtdShips = 0;
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

void setShips(Board* b, int* lst){
    
}