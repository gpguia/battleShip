#include "board.h"

int main(int argc, char *argv[]){
    
    Board *p1, *p2;
    int* lstOfShips;
    int random = 0;
    p1 = malloc(sizeof (Board));
    p2 = malloc(sizeof (Board));

    if(checkArgs(argc, argv)){
        newBoard(atoi(argv[1]), atoi(argv[2]), p1, p2);
    }else{
        int col, row;
        printWarningMsg("Specify the board size! Minimum size:20x20 ; Maximum size:40x40");
        printWarningMsg("Format of board sizes: X Y");
        scanf("%d%d",&row,&col);
        newBoard(row, col, p1, p2);
    }
    
    lstOfShips = selectChips(p1->rowSize,p1->colSize);
    setHP(p1,p2,lstOfShips);

    printWarningMsg("Player 1: Randomly set ships ?(" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
    scanf("%d",&random);
    while(random != 1 && random != 0){
		printf("\n" KNRM "Randomly set ships ? (" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
		scanf("%d",&random);
	}

	if(random == 1){
		//randomPlaceShips(p1);
	}else{
        // setManualyShips();
    }

    printWarningMsg("Player 2: Randomly set ships ?(" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
    scanf("%d",&random);
    while(random != 1 && random != 0){
		printf("\n" KNRM "Randomly set ships ? (" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
		scanf("%d",&random);
	}

    if(random == 1){
		//randomPlaceShips(p2);
	}else{
        // setManualyShips();
    }


    return 0;
}