#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define _PLAYER_   0
#define _SAVE_LOG_ 1
#include "libs/table.h"



Map m;
int main(){
	initiateMap(&m);
	while(1){game(&m);}	
	return 0;
}
