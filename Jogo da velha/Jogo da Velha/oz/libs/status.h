#ifndef STATUS_H
#define STATUS_H
#include "table.h"


// representa uma jogada na tabela
// juntamente com um peso
typedef struct {
	PWeight w;
	int i, j;	
} PlayPos;


typedef struct {
	// ultima jogada efetuada
	PlayPos last;
	const char* name;
} Status;

#endif
