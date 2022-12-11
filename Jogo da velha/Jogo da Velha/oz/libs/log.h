#ifndef LOG_FILE
#define LOG_FILE

#include <stdio.h>
#include <stdlib.h>
#include "table.h"

extern FILE* flog;

int openFile(const char* filename);
void closeFile();
void saveMap(Map* m);

#endif
