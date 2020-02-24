#include "battleShip.h"

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

int main (void){
    Board* b = newBoard(10,12);

    printf("%d\n", b->board[0][0]);

    printRules();

    clearBoard(b);
    return 0;
}
