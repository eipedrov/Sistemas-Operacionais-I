#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "IA.h"

char jogo[3][3];
char jogador1[50], jogador2[50];

void inicializarMatriz()
{
    int i,j;
    for(i = 0; i < 3; i ++)
    {
        for(j = 0; j <3; j++)
        {
            jogo[i][j]=' ';
        }
    }
}

int eValido(char letra)
{
    if(letra == 'x' || letra == '0')
        return 1;
    else
        return 0;
}

int coordenadaEhValida(int x, int y)
{
    if(x >= 0 && x < 3)
    {
        if(y >= 0 && y < 3)
            return 1;
    }
    return 0;
}

int posicaoVazia(int x, int y)
{
    if(jogo[x][y] != 'x' && jogo[x][y] != '0')
        return 1;
    return 0;
}

int ganhouLinhas()
{
    int i, j, igual = 1;
    for (i = 0; i < 3; i++)
    {
        for(j = 0; j < 2; j++)
        {
            if(eValido(jogo [i][j]) && (jogo [i][j]) == (jogo [i][j+1]))
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int ganhouColunas()
{
    int i, j, igual = 1;
    for (i = 0; i < 3; i++)
    {
        for(j = 0; j < 2; j++)
        {
            if(eValido(jogo [j][i]) && (jogo [j][i]) == (jogo [j+1][i]))
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int ganhouDiagPrincipal ()
{
    int i, igual = 1;
    for (i = 0; i < 2; i++)
    {
        if(eValido(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int ganhouDiagSecundaria ()
{
    int i, igual = 1;
    for (i = 0; i < 2; i++)
    {
        if(eValido(jogo[i][3-i-1]) && jogo[i][3-i-1] == jogo[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

void imprimir()
{
    system("cls");
    int lin, col;
    printf("\n\t    0  1  2\n ");
    for(lin = 0; lin < 3; lin++)
    {
        printf("\t%d ", lin);
        for(col = 0; col < 3; col++)
        {
            if(eValido(jogo[lin][col])){
                if(col < 2)

                    printf(" %c |", jogo[lin][col]);
                    else
                        printf(" %c ", jogo[lin][col]);
                }
                else
                {
                    if(col < 2)
                        printf("   |");
                    else
                        printf("   ");
                }
        }
        if(lin < 2)
            printf("\n\t   ---------\n");
    }
}

void setPlayer(){
    
    int turno = rand()%2;
    printf("-- %d --", turno);
    player[0] = ' '; // espaco vazio
    if(turno == 0){
        player[1] = 'x';
        player[2] = '0';
    } else {
        player[1] = '0';
        player[2] = 'x';
    }

}

void jogarIA()
{
    int x, y, valida, jogadas = 0, ganhou = 0, ordem = 1;
    do
    {
        do
        {        	
        	imprimir();
        	BetterPosition bp;
        	computeIA (jogo, &bp, ordem);
            x = bp.x;
            y = bp.y;
        	sleep(1);
            valida = coordenadaEhValida(x, y);
            if (valida == 1)
                valida += posicaoVazia(x, y);
        }
        while(valida != 2);

        if(ordem == 1)
            jogo[x][y] = player[1];
        else
            jogo[x][y] = player[2];

        jogadas++;

        ordem++;
        if(ordem ==3)
            ordem =1;
        ganhou += ganhouLinhas();
        ganhou += ganhouColunas();
        ganhou += ganhouDiagPrincipal();
        ganhou += ganhouDiagSecundaria();

    }
    while(ganhou == 0 && jogadas < 9);
    if(ganhou !=0)
    {
        imprimir();
        if(ordem -1 == 1)
            printf("\nParabens, o primeiro jogador venceu!\n\n");
        else
            printf("\nParabens, o segundo jogador venceu!\n\n");        
    } else {
        imprimir();
        printf("\nQue feio, ninguem venceu!\n\n");
    }
    setPlayer();
    srand(time(NULL));
}

int main()
{
    int op;
    do
    {
        inicializarMatriz();
        setPlayer();
        jogarIA();
        printf("\nDeseja jogar novamente?\n1 - Sim\n2 - Nao\n");
        scanf("%d", &op);
    }
    while(op == 1);



    return 0;
}