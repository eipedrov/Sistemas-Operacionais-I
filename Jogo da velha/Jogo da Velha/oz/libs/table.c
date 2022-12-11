#include <stdio.h>
#include "table.h"
#include "tictactoeIA.h"
#include "log.h"
#include <unistd.h>
#include <time.h>

int INDEX_PLAYING 		= -1;
int GAME_INITIALIZED 	=  0;

void initiateMap(Map* m){
		
	// inicializa o gerador de pseudo-numeros aleatorios
	srand(time(NULL));
	
	if(GAME_INITIALIZED == 0){
		int i;
		for(i = 0; i < 2; i++)m->players[i].score = 0;
		GAME_INITIALIZED = 1;
	}
		
		
	m->usedCells = 0;
	
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			m->m[i][j].bit = E;
		}
	}	
	// chama o metodo para selecionar o token do 
	// player
	selectToken(m);
}

Token otherToken(Token t){
	return (t == X) ? O : X;
}

int TokenComparator(Cell* c, Token t){
	return c->bit == t;
}

int compareTokens(Token a, Token b, Token c){
	return (a == b) && (b == c);
}

Player* playerByToken(Map* m, Token t){
	
	int i, nToken = 2;
	for(i = 0; i < nToken; i++)
		if(m->tokens[i] == t)
			return &m->players[i];
	
	return NULL;
	
}

void selectToken(Map* m){
	int token;
#if _PLAYER_
	printf("Digite seu token: X(0) or O(1): ");
	scanf("%d", &token);
#else
	token = rand()%1;
#endif
	m->tokens[0] = (Token)token; // player token
	m->tokens[1] = otherToken((Token)token); // IA token

}

void dMap(Map* m){
	int i, j;
	
	printf("Seu Token: %c \t IA Token: %c\n",
		parseTable(m->tokens[0]), parseTable(m->tokens[1]));
		
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf(" %c ", parseTable(m->m[i][j].bit));
			if(j < 2)printf(" | ");
		}
		printf("\n");
	}	
}

void dScorePlayers(Map* m){
	int i;
	for(i = 0; i < 2; i++){
		printf("Player[%d]: %d\n", i, m->players[i].score);
	}
}


char parseTable(Token t){
	switch(t){
		case X : return 'X';
		case O : return 'O';
		default: return 'E';
	}
}

void playing(Map* m, Token t, int i, int j){
	if(m->m[i][j].bit == E){
		m->m[i][j].bit = t;
	} else {
		printf("N�o foi possivel jogar nessa posicao!\n");
	}
}

Token cellToken(Cell* c){
//	printf("Token testado -> %c\n", parseTable(c->bit));
	return c->bit;
}

Token hasWinner(Map* m){
	int i;
	
	printf("linhas\n");
	// ganhando por linha
	for(i = 0; i < 3; i++){
		if(compareTokens(
			cellToken(&m->m[i][0]),
			cellToken(&m->m[i][1]),
			cellToken(&m->m[i][2])
		)){return cellToken(&m->m[i][0]);};
	}
	printf("colunas\n");	
	// ganhando por Coluna
	for(i = 0; i < 3; i++){
		if(compareTokens(
			cellToken(&m->m[0][i]),
			cellToken(&m->m[1][i]),
			cellToken(&m->m[2][i])
		)){return cellToken(&m->m[0][i]);};
	}
	printf("diagonal\n");
	// ganhando por diagonal
	if(compareTokens(
		cellToken(&m->m[0][0]),
		cellToken(&m->m[1][1]),
		cellToken(&m->m[2][2])
	)){return cellToken(&m->m[0][0]);};
	
	if(compareTokens(
		cellToken(&m->m[2][0]),
		cellToken(&m->m[1][1]),
		cellToken(&m->m[0][2])
	)){return cellToken(&m->m[2][0]);};
	printf("ninguem ganhou\n");
	return E;
	
}

void game(Map* m){
	int i, j;
	Token t;
	
	// desneha os pontos
	dScorePlayers(m);
	// desenhar o mapa
	dMap(m);
	
	if(INDEX_PLAYING == -1)
		INDEX_PLAYING = rand()%1;
	int pos;
	if(m->tokens[0] == INDEX_PLAYING){
//		do {
//			printf("Escolha uma posicao de 0..8: ");
//			scanf("%d", &pos);
//			i = (int)pos/3;
//			j = pos%3;
//			
//			if(pos < 0 || pos > 8)
//				continue;
//			if(!TokenComparator(&m->m[i][j],E))
//				continue;
//			break;	
//		} while(1);
//		playing(m, m->tokens[0], i, j);	
		printf("IA(0) jogando...\n");
		sleep(1);
		computeIA(m, O);	
	} else {
		printf("IA(1) jogando...\n");
		sleep(1);
		computeIA(m, X);
	}
		
	if((t = hasWinner(m)) != E){
		dMap(m);
		printf("O jogador %c foi o vencedor!\n", parseTable(t));
		sleep(1);
		
		// incrementando 1 ponto no vencedor
		Player* p = playerByToken(m, t);
		p->score++;

		saveMap(m);

		initiateMap(m);
		// getchar();
		return;
	}
	
	if(m->usedCells == MAX_USED_CELLS){
		dMap(m);
		printf("Jogo empatado!!\n");
		sleep(1);
		initiateMap(m);	
		return;
	}
	
	INDEX_PLAYING = INDEX_PLAYING == 0 ? 1 : 0;
	system("cls");
}
