#include <stdio.h>
#include <stdlib.h>

#include "table.h"
#include "status.h"

typedef void(*PCallback)(Map*, Token, int, int);

void computeIA(Map* m, Token tIA);
void betterChoice(Map* m, Token tIA, PlayPos* pp, PCallback play);
void iaHelper(
	Token token,
	Token tIA,
	PlayPos* pp,
	int i,
	int j
);

void caseLines		(Map* m, int tIndex, Token tIA, PlayPos* pp);
void caseColumns	(Map* m, int tIndex, Token tIA, PlayPos* pp);
void caseDiagonal	(Map* m, int tIndex, Token tIA, PlayPos* pp);

void computeIA(Map* m, Token tIA){
	
	// verifica se existe dois valores
	// em sequencia faltando somente 1
	// para ganhar ou perder.
	/* c0   c1  c2
	l0	0	1	2
	l1	3 	4 	5
	l2	6	7	8
	*/
	
	int i, j;	
	// caso tenha uma jogada em que o player sairá
	// vencedor
	PlayPos pp = {NONE, -1, -1};
	for(i = 0; i < 2; i++){		
		
		/* 
			i == 0 -> Player token
			i == 1 -> IA token
		*/		
		caseLines   (m, i, tIA, &pp);					
		caseColumns (m, i, tIA, &pp);
		caseDiagonal(m, i, tIA, &pp);	
		
	}
	
	betterChoice(m, tIA, &pp, playing);
	
} 

void betterChoice(Map* m, Token tIA, PlayPos* pp, PCallback play){
	printf("Play Pos: %d %d\n", pp->i, pp->j);
	if(pp->i == -1 && pp->j == -1){
		int i, j;
		do {
			i = rand()%3;
			j = rand()%3;
			printf("%d %d\n", i, j);
		} while(!TokenComparator(&m->m[i][j], E));
		play(m, tIA, i, j);
	} else {play(m, tIA, pp->i, pp->j);}
	// reseta a jogada, para dar inicio a uma nova
	pp->w = NONE;
	pp->i = -1;
	pp->j = -1;
	m->usedCells++;
}

// 
//
void iaHelper(Token token, Token tIA, PlayPos* pp, int i, int j){
	
	PWeight pw;
	if(token == otherToken(tIA))
		pw = LOSS;
	else if(token == tIA)
		pw = WIN;
	
	if(pp->w == WIN)
		return;
		
	if(pp->w == NONE){
		pp->w = pw;
		pp->i = i;
		pp->j = j;
	}		
	
	if(pp->w == LOSS){
		
		if(pw == WIN){
			pp->w = pw;
			pp->i = i;
			pp->j = j;
		}
		
	}
	
}

void caseLines(Map* m, int tIndex, Token tIA, PlayPos* pp){
	int i = tIndex, j;
	// Caso 1
	for(j = 0; j < 3; j++){
		
		if(
			TokenComparator(&m->m[j][0], m->tokens[i]) &&
			TokenComparator(&m->m[j][1], m->tokens[i]) &&
			TokenComparator(&m->m[j][2], E)
		)
		// player será o vencedor no caso 
		/*
		j=0	? - ? - 2
		j=1	3 - 4 - 5
		j=2	6 - 7 - 8		
		*/
		{iaHelper(m->tokens[i], tIA, pp, j, 2);}
		
		if(
			TokenComparator(&m->m[j][0], E) &&
			TokenComparator(&m->m[j][1], m->tokens[i]) &&
			TokenComparator(&m->m[j][2], m->tokens[i])				
		)
		// player será o vencedor no caso 
		/*
		j=0	0 - ? - ?
		j=1	3 - 4 - 5
		j=2	6 - 7 - 8		
		*/
		{iaHelper(m->tokens[i], tIA, pp, j, 0);}
		
		// caso extra 1.0
		if(
			TokenComparator(&m->m[j][0], m->tokens[i]) &&
			TokenComparator(&m->m[j][1], E) &&
			TokenComparator(&m->m[j][2], m->tokens[i])			
		)
		// player será o vencedor no caso 
		/*
		j=0	? - 1 - ?
		j=1	3 - 4 - 5
		j=2	6 - 7 - 8		
		*/
		{iaHelper(m->tokens[i], tIA, pp, j, 1);}
	
	}
}
void caseColumns(Map* m, int tIndex, Token tIA, PlayPos* pp){
	int i = tIndex, j;
	// Caso 2
	for(j = 0; j < 3; j++){		
		if(
			TokenComparator(&m->m[0][j], m->tokens[i]) &&
			TokenComparator(&m->m[1][j], m->tokens[i]) &&
			TokenComparator(&m->m[2][j], E)
		)
		// player será o vencedor no caso 
		/*
		    j=0 j=1 j=1
			?  - 2  - 3 
			?  - 4  - 5
			6  - 7  - 8		
		*/
		{iaHelper(m->tokens[i], tIA, pp, 2, j);}
		
		if(
			TokenComparator(&m->m[0][j], E) &&
			TokenComparator(&m->m[1][j], m->tokens[i]) &&
			TokenComparator(&m->m[2][j], m->tokens[i])				
		)
		// player será o vencedor no caso 
		/*
		    j=0 j=1 j=1
			0  - 2  - 3 
			?  - 4  - 5
			?  - 7  - 8		
		*/
		{iaHelper(m->tokens[i], tIA, pp, 0, j);}
		
		// caso extra 2.0
		if(
			TokenComparator(&m->m[0][j], m->tokens[i]) &&
			TokenComparator(&m->m[1][j], E) &&
			TokenComparator(&m->m[2][j], m->tokens[i])
		)
		// player será o vencedor no caso 
		/*
		    j=0 j=1 j=2
			?  - 1  - 2
			3  - 4  - 5
			?  - 7  - 8		
		*/
		{iaHelper(m->tokens[i], tIA, pp, 1, j);}
		
	}
}
void caseDiagonal(Map* m, int tIndex, Token tIA, PlayPos* pp){
	int i = tIndex;
	// caso 3
	// 3.1
	if(
		TokenComparator(&m->m[0][0], m->tokens[i]) &&
		TokenComparator(&m->m[1][1], m->tokens[i]) &&
		TokenComparator(&m->m[2][2], E)
	)
	// player será o vencedor no caso 
	/*
		? - 2 - 3
		4 - ? - 5
		6 - 7 - 8		
	*/
	{iaHelper(m->tokens[i], tIA, pp, 2, 2);}
	
	// caso extra 3.1
	if(
		TokenComparator(&m->m[0][0], m->tokens[i]) &&
		TokenComparator(&m->m[1][1], E) &&
		TokenComparator(&m->m[2][2], m->tokens[i])
	)
	// player será o vencedor no caso 
	/*
		? - 1 - 2
		3 - 4 - 5
		6 - 7 - ?		
	*/
	{iaHelper(m->tokens[i], tIA, pp, 1, 1);}
	
	// 3.2
	if(
		TokenComparator(&m->m[1][1], m->tokens[i]) &&
		TokenComparator(&m->m[2][2], m->tokens[i]) &&
		TokenComparator(&m->m[0][0], E)
	)
	// player será o vencedor no caso 
	/*
		1 - 2 - 3
		4 - ? - 5
		6 - 7 - ?		
	*/
	{iaHelper(m->tokens[i], tIA, pp, 0, 0);}
	
	// caso extra 3.2
	if(
		TokenComparator(&m->m[0][0], m->tokens[i]) &&
		TokenComparator(&m->m[1][1], E) &&
		TokenComparator(&m->m[2][2], m->tokens[i]) 
	)
	// player será o vencedor no caso 
	/*
		? - 1 - 2
		3 - 4 - 5
		6 - 7 - ?		
	*/
	{iaHelper(m->tokens[i], tIA, pp, 1, 1);}
	
	// 3.3
	if(
		TokenComparator(&m->m[2][0], m->tokens[i]) &&
		TokenComparator(&m->m[1][1], m->tokens[i]) &&
		TokenComparator(&m->m[0][2], E)
	)
	// player será o vencedor no caso 
	/*
		1 - 2 - 3
		4 - ? - 5
		? - 7 - 8		
	*/
	{iaHelper(m->tokens[i], tIA, pp, 0, 2);}
	
	// caso extra 3.3
	if(
		TokenComparator(&m->m[2][0], m->tokens[i]) &&
		TokenComparator(&m->m[1][1], E) &&
		TokenComparator(&m->m[0][2], m->tokens[i])

	)
	// player será o vencedor no caso 
	/*
		0 - 1 - ?
		3 - 4 - 5
		? - 7 - 8		
	*/
	{iaHelper(m->tokens[i], tIA, pp, 1, 1);}
	
	// 3.4
	if(
		TokenComparator(&m->m[1][1], m->tokens[i]) &&
		TokenComparator(&m->m[0][2], m->tokens[i]) &&
		TokenComparator(&m->m[2][0], E)
	)
	// player será o vencedor no caso 
	/*
		1 - 2 - ?
		4 - ? - 5
		6 - 7 - 8		
	*/
	{iaHelper(m->tokens[i], tIA, pp, 2, 0);}
}

