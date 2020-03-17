#include "battleShip.h"

int main (void){
	// printRules();

	int tmp=0;
	int turn=1;
	int coordX,coordY;
	Coordinate shot;

	askForInputs();
	
    
    Board* p1 = newBoard(bheight,blength);
	// Board* p2 = newBoard(bheight,blength);

	// randomPlaceShips(p1);
	// Ship s6;
	// s6.isAlive = true;
    // s6.length = TSHAPE_SIZE;
    // s6.type = TSHAPE;
    // s6.shotsRecived = 0;
	// s6.start.row = 7;
	// s6.start.col = 7;
	// s6.isHorizontal = true;
	// setShipPos(p1,s6);

	// printBoard(p1);


	// randomPlaceShips(p1);
  	// printf("\n");
	// printf("\t\t\tPLayer1\n");
	// printf("\n");
  	// randomPlaceShips(p2);
	// printBoard(p2);
	// Ship s;
	// s.isAlive = true;
	// s.length = CARRIER_SIZE;
	// s.type = CARRIER;
	// s.start.col = 0;
	// s.start.row = 1;
	// s.isHorizontal = false;
	// setShipPos(p1,s);
	// shot.col = 0;
	// shot.row = 5;
	// shoot(p1,shot,0);
	// shot.col = 1;
	// shot.row = 5;
	// shoot(p1,shot,0);
	// printBoard(p1);
  	// printf("\n");
	// printf("\t\t\tPLayer2\n");
	// printf("\n");
  	// printBoard(p2);

  	// while(tmp==0){
  	// 	if(turn==1){
  	// 		for(int i=0; i<3; i++){
  	// 			scanf("%d %d",&coordX,&coordY);
  	// 			shot.row=coordY;
  	// 			shot.col=coordX;
  	// 			shoot(p1,p2,shot);
  	// 			printf("\n");
	// 			printf("\t\t\tPLayer1\n");
	// 			printf("\n");
  	// 			printBoard(p1);
  	// 			printf("\n");
	// 			printf("\t\t\tPLayer2\n");
	// 			printf("\n");  				
  	// 			printBoard(p2);
  	// 		}
  	// 		turn=0;	
  	// 	}
  	// 	if(turn==0){
  	// 		for(int i=0; i<3; i++){
  	// 			scanf("%d %d",&coordX,&coordY);
  	// 			shot.row=coordY;
  	// 			shot.col=coordX;
  	// 			shoot(p2,p1,shot);
  	// 			printf("\n");
	// 			printf("\t\t\tPLayer1\n");
	// 			printf("\n");  				
  	// 			printBoard(p1);
  	// 			printf("\n");
	// 			printf("\t\t\tPLayer2\n");
	// 			printf("\n");  				
  	// 			printBoard(p2);	
  	// 		}	
  	// 	}	
  	// }
  	
    clearBoard(p1);
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
	printf("   *Após jogada jogador que realizou os tiros deve marcar nas coordenadas atiras com :\n ");
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


}