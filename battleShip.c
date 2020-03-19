#include "battleShip.h"

int main (void){
	// printRules();

	int col,row;
	Board* p1board;
	Board* p2board;
	Coordinate shot;

	p1board = askForInputs();

	col = p1board->colSize;
	row = p1board->rowSize;
	p2board = newBoard(row,col);

	randomPlaceShips(p2board);

	shotsfired(p1board,p2board);

    //clearBoard(p1);
    // clearBoard(p2);
    return 0;
}


void printRules(){
	printf("   Batalha Naval é um jogo de tabuleiro de apenas 2 jogadores com um unico objetivo, tentar adivinhar a localização dos navios de guerra do adversario. \n");
	printf("   Teremos dois modos de jogo : Automático e Manual.\n");
	printf("       -No modo automático serão escolhidas as posições dos navio de forma aleatória.\n");
	printf("       -No modo Manual cada jogador pode posicionar os navios da forma que pretende.\n");
	printf("\n");
	printf("   Regras de preparação do jogo: \n");
	printf("   * Navios podem ter variada dimensão , dimensão esta marcada por quadriculas. Cada quadricula tem um coordenadas X e uma Y. \n");
	printf("   * Não podem ser sobrepostos navios. \n");
	printf("   * Batalha é jogada por alternadamente entre os jogadores. \n");
	printf("\n");
	printf("   Regras de jogo: \n");
	printf("   * Primeiro jogador , escolhido sorteadamente, dá coordenadas de 3 tiros por jogada (X e Y da quadricula do tiro) \n");
	printf("   * Adversário terá de responder com: \n");
	printf("   		-AGUA - tiro nao acertou em nenhuma parte de nenhum navio. \n");
	printf("   		-FOGO - tiro acertou numa parte pertencente a um dos navios. \n");
	printf("   		-AFUNDOU - tiro acertou numa parte do navio , completando assim todas as partes do navio e adundando-o. \n");
	printf("   *Após jogada jogador que realizou os tiros deve marcar nas coordenadas atiradas com :\n ");
	printf("        - uma bola (caso tenha acertado na agua) \n");
	printf("        - um X (caso tenha acertado num dos navios) \n");
	printf("   *Alterna-se a vez de jogar para o outro jogador. \n");
	printf("\n");
	printf("\n");
	printf("   Jogo termina quando após varias jogadas um dos jogadores conseguir derrubar todos os navios do adversário \n");
}

Board* askForInputs(){
	int h,w;
	Board* b;
	int ok = -1;

	printf("Specify the board size! Minimum size:10x10 ; Maximum size:36x36 \n");
	printf("Format of board sizes:X Y \n");
	scanf("%d%d",&h,&w);

	while(h < 10 || h > 36 || w < 10 || w > 36){
		printf("Incorrect sizes (Minimum size:10x10 ; Maximum size:36x36)\n");
		printf("Introduce new format:\n");
		scanf("%d%d",&h,&w);
	}

	b = newBoard(h,w);

	printf(KNRM "Board size set to: " KGRN "(%d,%d)\n",h,w);

	while(ok != 1 && ok != 0){
		printf("\n" KNRM "Randomly set ships ? (" KGRN "1" KNRM "/" KRED "0" KNRM "): ");
		scanf("%d",&ok);
	}

	if(ok == 1){
		randomPlaceShips(b);
	}

	return b;
}


void shotsfired(Board* p1board, Board* p2board){
	int tmp=0;
	int turn=1;
	Coordinate shot;
	int r,c;
	Shots* p;

	globalprint(p1board,p2board);

	while(tmp != 1){

		if(turn == 1){
			printf("PLAYER1 Introduce 3 shots coordinates (R C):\n");
			for(int i=0;i<3;i++){
				printf("Shot %d:" ,i+1);
				scanf("%d %d",&r,&c);
				shot.row=r;
				shot.col=c;
				p=searchShot(p2board->shotsFierd,shot);
				while(r<0 || c<0 ||  r>p1board->rowSize || c >= p1board->colSize || p!=NULL ){
					printf(KRED "That is an invalid Coordinate, please respect the board edges.\n" KNRM);
					printf("PLAYER1 Introduce 3 shots coordinates (R C):\n");
					printf("Shot %d:" ,i+1);
					scanf("%d %d",&r,&c);
				}
				shot.row=r;
		  	shot.col=c;
				shoot(p2board,shot,turn);
				globalprint(p1board,p2board);
				if(verifyendgame() == true){
					printf("PLAYER1 WIN");
					tmp=1;
					return;
				}
			}
			turn=2;
		}

		if(turn == 2){
			printf("PLAYER2 Introduce 3 shots coordinates (R C):\n");
			for(int j=0; j<3;j++){
				printf("Shot %d:" ,j+1);
				scanf("%d %d",&r,&c);
				while(r<0 || c<0 ||  r>p1board->rowSize || c >= p1board->colSize){
					printf(KRED "That is an invalid Coordinate, please respect the board edges.\n" KNRM);
					printf("PLAYER2 Introduce 3 shots coordinates (R C):\n");
					printf("Shot %d:" ,j+1);
					scanf("%d %d",&r,&c);
				}
				shot.row=r;
		  	shot.col=c;
				shoot(p1board,shot,turn);
				globalprint(p1board,p2board);
				if(verifyendgame() == true ){
					printf("PLAYER2 WIN");
					tmp=1;
					return;
				}
			}
			turn=1;
		}

	}

}


void globalprint(Board* p1board,Board* p2board){

	printf("\t\t\t\t\tPlayer1 \n");
	printf("\n");
	printBoard(p1board,p2board);
	printf("\t\t\t\t\tPlayer2 \n");
	printf("\n");
	printBoard(p2board,p1board);
}
