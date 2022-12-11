#include "log.h"

FILE* flog = NULL;

int openFile(const char* filename){
	flog = fopen(filename, "w");
	if(flog != NULL)
		return 1;
	return 0;
}

void closeFile(){
	if(flog != NULL)
		fclose(flog);
}

void saveMap(Map* m){
	int err;
	char buffer[512];
	
	if(flog == NULL){
		err = openFile("log.txt");
		if(!err) exit(-1);
	}
	
	char t[9];
	int i, j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			t[i * 3 + j] = parseTable(m->m[i][j].bit);
	
	sprintf(buffer,
		" %c | %c | %c\n %c | %c | %c\n %c | %c | %c\n\n",
		t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7], t[8]
	);
	
	fprintf(flog, "%s", buffer);
	
//	closeFile(flog);
	
}
