#ifndef TABLE_H
#define TABLE_H

#define MAX_USED_CELLS 9

typedef enum {
	X = 0, // token de jogador
	O, // token de jogador
	E  // token de lugar vazio 
} Token;

typedef enum {
	LOSS,
	WIN,
	NONE
} PWeight;

// representação de uma celula do tabuleiro
typedef struct {
	Token bit; 
} Cell;

typedef struct {
	int score;
} Player;

// representação do tabuleiro
// - Obs .: um array bi-dimensional de 3x3 (9 celulas)
typedef struct {
	int usedCells;
	Player players[2];
	// tokens[0] -> Player
	// tokens[1] -> IA
	Token tokens[2];
	Cell m[3][3];
} Map;

extern int INDEX_PLAYING;
extern int GAME_INITIALIZED;

// inicia o mapa com todos as celulas
// vazias
void initiateMap(Map* m);
// seleciona o token do jogador
void selectToken(Map* m);
// retorna o outro token diferente do passado
Token otherToken(Token t);
// compara o token de uma celula com outro token
int TokenComparator(Cell* c, Token t);

int compareTokens(Token a, Token b, Token c);

void dScorePlayers(Map* m);
Player* playerByToken(Map* m, Token t);

// desenha o mapa no console
void dMap(Map* m);
// faz o parse do enum para uma representação
// visial melhor
char parseTable(Token t);
// faz uma jogada numa determinada posição
// da tabela
void playing(Map* m, Token t, int i, int j);

Token cellToken(Cell* c);
Token hasWinner(Map* m);
int isFinished(Map* m);
// game main loop
void game(Map* m);

#endif

