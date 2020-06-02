#include "ship.h"

void printAllShipsTypes(){

    printf("\nName: Carrier: \t Battleship: \t Cruiser:\tSubmarine:\tDestroyer:\tTShape: \n");
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

void sumShipSizesAndSetHP(int *lstOfShips, int *p1Hp, int *p2Hp){
    for(int i=0;i<6;i++){
        switch (i)
        {
        case CARRIER:
            *p1Hp += CARRIER_SIZE * lstOfShips[i];
            *p2Hp += CARRIER_SIZE * lstOfShips[i];
            break;
        case BATTLESHIP:
            *p1Hp += BATTLESHIP_SIZE * lstOfShips[i];
            *p2Hp += BATTLESHIP_SIZE * lstOfShips[i];
            break;
        case CRUISER:
            *p1Hp += CRUSIER_SIZE * lstOfShips[i];
            *p2Hp += CRUSIER_SIZE * lstOfShips[i];
            break;
        case SUBMARINE:
            *p1Hp += SUBMARINE_SIZE * lstOfShips[i];
            *p2Hp += SUBMARINE_SIZE * lstOfShips[i];
            break;
        case DESTROYER:
            *p1Hp += DESTROYER_SIZE * lstOfShips[i];
            *p2Hp += DESTROYER_SIZE * lstOfShips[i];
            break;
        case TSHAPE:
            *p1Hp += (TSHAPE_SIZE + 2) * lstOfShips[i];
            *p2Hp += (TSHAPE_SIZE + 2) * lstOfShips[i];
            break;
        }
    }
}
