#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum { LOSS, WIN, NONE };
struct better_position {  int x, y; };
typedef struct better_position BetterPosition;

// char player[] = {' ', 'x', '0'};
char player[3];

// char mapa[3][3] = {
//     {'x', ' ', ' '},
//     {' ', 'x', ' '},
//     {' ', ' ', ' '}
// };

int comp(char a, char b){
    return a == b;
}

char otherPlayer(int ordem){
    return ordem == 1 ? player[2] : player[1];
}

int otherPlayerOrdem(int ordem){
    return ordem == 1 ? 2 : 1;
}

void lines(char (*mapa)[3], BetterPosition* bp, int ord){
    int i;
    for(i = 0; i < 3; i++){
        // caso 1
        if(
            comp(mapa[i][0], player[ord]) &&
            comp(mapa[i][1], player[ord]) &&
            comp(mapa[i][2], player[0])
        ){ 
            bp->x = i;
            bp->y = 2;
        };

        // caso 2
        if(
            comp(mapa[i][0], player[0]) &&
            comp(mapa[i][1], player[ord]) &&
            comp(mapa[i][2], player[ord])
        ){ 
            bp->x = i;
            bp->y = 0;
        };

        // caso 3
        if(
            comp(mapa[i][0], player[ord]) &&
            comp(mapa[i][1], player[0]) &&
            comp(mapa[i][2], player[ord])
        ){ 
            bp->x = i;
            bp->y = 1;
        };

    }
        
}

void columns(char (*mapa)[3], BetterPosition* bp, int ord){
    int j;
    for(j = 0; j < 3; j++){

        // caso 1
        if(
            comp(mapa[0][j], player[ord]) &&
            comp(mapa[1][j], player[ord]) &&
            comp(mapa[2][j], player[0])
        ){
            bp->x = 2;
            bp->y = j;
        }

        // caso 2
        if(
            comp(mapa[0][j], player[0]) &&
            comp(mapa[1][j], player[ord]) &&
            comp(mapa[2][j], player[ord])
        ){
            bp->x = 0;
            bp->y = j;
        }

        // caso 3
        if(
            comp(mapa[0][j], player[ord]) &&
            comp(mapa[1][j], player[0]) &&
            comp(mapa[2][j], player[ord])
        ){
            bp->x = 1;
            bp->y = j;
        }

    }
}

void diagonal(char (*mapa)[3], BetterPosition* bp, int ord){

    if(
        comp(mapa[0][0], player[ord]) &&
        comp(mapa[1][1], player[ord]) &&
        comp(mapa[2][2], player[0])
    ){bp->x = 2; bp->y = 2;}

    if(
        comp(mapa[0][0], player[ord]) &&
        comp(mapa[1][1], player[0])   &&
        comp(mapa[2][2], player[ord])
    ){bp->x = 1; bp->y = 1;}

    if(
        comp(mapa[0][0], player[0])   &&
        comp(mapa[1][1], player[ord]) &&
        comp(mapa[2][2], player[ord])
    ){bp->x = 0; bp->y = 0;}

    // caso 3.3
    if(
        comp(mapa[2][0], player[ord]) &&
        comp(mapa[1][1], player[ord]) &&
        comp(mapa[0][2], player[0])
    ){bp->x = 0; bp->y = 2;}

    // caso 3.4
    if(
        comp(mapa[2][0], player[ord]) &&
        comp(mapa[1][1], player[0])   &&
        comp(mapa[0][2], player[ord])
    ){bp->x = 1; bp->y = 1;}

    // caso 3.5
    if(
        comp(mapa[1][1], player[ord]) &&
        comp(mapa[0][2], player[ord]) &&
        comp(mapa[2][0], player[0])
    ){bp->x = 2; bp->y = 0;}

}

void computeIA(char (*mapa)[3], BetterPosition* bp, int ordem){
    
    // reseta a melhor posicao anterior
    bp->x = -1;
    bp->y = -1;
    
    BetterPosition _bp[3] = {
        {-1 , -1}, // vago
        {-1 , -1}, // ordem 1
        {-1 , -1}, // ordem 2
    };

    int i;
    for(i = 1; i <= 2; i++){
        lines   (mapa, &_bp[i], i);
        columns (mapa, &_bp[i], i);
        diagonal(mapa, &_bp[i], i);
    }

    int x, y, otherPlayer;
    otherPlayer = otherPlayerOrdem(ordem);

    // verificando se o player da ordem vai perder
    if(
        _bp[otherPlayer].x != -1 &&
        _bp[otherPlayer].y != -1
    ){
        // a melhor jogada no momento
        bp->x = _bp[otherPlayer].x;
        bp->y = _bp[otherPlayer].y;
    }

    // caso o outro player nao ganhe, verifica
    // se o player da ordem tem uma jogada de vitoria
    if(_bp[ordem].x != -1 && _bp[ordem].y != -1){
        // melhor jogada no momento
        bp->x = _bp[ordem].x;
        bp->y = _bp[ordem].y;
    } 
    
    // caso mesmo apos as verificacoes, ainda continue 
    // sem uma jogada previa
    if(bp->x == -1 && bp->y == -1) {
        // caso nao tenha uma jogada previa, escolha uma
        // posicao livre
        do {
			x = rand()%3;
			y = rand()%3;			
		} while(!comp(mapa[x][y], player[0]));
        bp->x = x; 
        bp->y = y;
    }


}

// int main(void)
// {
//     BetterPosition bp;
//     computeIA(mapa, &bp, 2);    
//     printf("better position: x = %d | y = %d\n", bp.x, bp.y); 
//     return 0;

// }

#endif