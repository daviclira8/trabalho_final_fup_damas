/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Essa função será responsável por validar as jogadas, verificando a sintaxe e o formato da entrada, validando as coordenadas, as peças e as regras de movimento. 
//Declarar essas variaveis será util para transformar as entradas em algo legivel dentro de uma matriz 10x10.

int validar_jogada(char tabuleiro[tam_tabuleiro][tam_tabuleiro], char *entrada, char jogadoratual, int modojogo, int linha_artigo){
    if(strlen(entrada) != 6) return 0;
    if(!(entrada[0] >= 'A' && entrada[0] <= 'J'
         && entrada[1] >= '0' && entrada[1] <= '9' 
         && entrada[2] == '-' && entrada[3] == '-' 
         && entrada[4] >= 'A' && entrada[4] <= 'J' 
         && entrada[5] >= '0' && entrada[5] <= '9')) return 0;
    int colin = entrada[0] - 'A';
    int linin = entrada[1] - '0'; 
    int colfim = entrada[4] - 'A';
    int linfim = entrada[5] - '0';
}

int ehposicaovalida(int lin, int col){
    if(lin >= 0 && lin <= tam_tabuleiro - 1 && col >= 0 && col <= tam_tabuleiro - 1){
        if((lin + col) % 2 == 1) return 1;
    }
    return 0;
}
void promoverpeca(char tabuleiro[tam_tabuleiro][tam_tabuleiro], int lin, int col){
    
}
