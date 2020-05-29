
#define QT

#ifdef MATRIX
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
    
    lstOfShips = selectShips(p1->rowSize,p1->colSize);
    setHP(p1,p2,lstOfShips);
        
    printAllShipsTypes();
    printWarningMsg("Player 1: Randomly set ships ?(" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
    scanf("%d",&random);
    while(random != 1 && random != 0){
		printf("\n" KNRM "Randomly set ships ? (" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
		scanf("%d",&random);
	}

	if(random == 1){
		randomPlaceShips(p1,lstOfShips);
	}else{
        manualyPlanceShips(p1,lstOfShips);
    }

    printWarningMsg("Player 2: Randomly set ships ?(" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
    scanf("%d",&random);
    while(random != 1 && random != 0){
		printf("\n" KNRM "Randomly set ships ? (" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
		scanf("%d",&random);
	}

    if(random == 1){
		randomPlaceShips(p2,lstOfShips);
	}else{
        manualyPlanceShips(p2,lstOfShips);
    }

    fire(p1,p2);

    clearBoard(p1);
    clearBoard(p2);

    return 0;
}
#endif

#ifdef QT

#include "quadtree.h"

int main(int argc, char *argv[]){
    
    QD_NODE *p1, *p2;
    int p1Hp = 0, p2Hp = 0, random, rowSize, colSize;
    Coordinate c1, c2;
    Shots *p1Shots = NULL;
    Shots *p2Shots = NULL;
    
    int *lstOfShips;

    if(checkArgs(argc, argv)){
        int side = (atoi(argv[1]) == 20)?32:64;
        rowSize = atoi(argv[1]);
        colSize = atoi(argv[2]);
        c1 = make_point(0,side);
        c2 = make_point(side,0);
        p1 = newQuadLeaf(c1,c2);
        p2 = newQuadLeaf(c1,c2);
    }else{
        int col, row;
        printWarningMsg("Specify the board size! Minimum size:20x20 ; Maximum size:40x40");
        printWarningMsg("Format of board sizes: X Y");
        scanf("%d%d",&row,&col);
        int side = (row == 20)?32:64;
        rowSize = atoi(argv[1]);
        colSize = atoi(argv[2]);
        c1 = make_point(0,side);
        c2 = make_point(side,0);
        p1 = newQuadLeaf(c1,c2);
        p2 = newQuadLeaf(c1,c2);
    }
    
    lstOfShips = selectShips(rowSize,colSize);
    sumShipSizesAndSetHP(lstOfShips, &p1Hp, &p2Hp);    

    printTree(p1, rowSize, colSize);

    // printAllShipsTypes();
    // printWarningMsg("Player 1: Randomly set ships ?(" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
    // scanf("%d",&random);
    // while(random != 1 && random != 0){
	// 	printf("\n" KNRM "Randomly set ships ? (" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
	// 	scanf("%d",&random);
	// }

	// if(random == 1){
	// 	randomPlaceShips(p1,lstOfShips);
	// }else{
    //     manualyPlanceShips(p1,lstOfShips);
    // }

    // printWarningMsg("Player 2: Randomly set ships ?(" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
    // scanf("%d",&random);
    // while(random != 1 && random != 0){
	// 	printf("\n" KNRM "Randomly set ships ? (" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
	// 	scanf("%d",&random);
	// }

    // if(random == 1){
	// 	randomPlaceShips(p2,lstOfShips);
	// }else{
    //     manualyPlanceShips(p2,lstOfShips);
    // }

    return 0;
}
#endif
