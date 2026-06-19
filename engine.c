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
    //convertendo para numero legiveis em uma matriz 10x10;
    int colin = entrada[0] - 'A';
    int linin = entrada[1] - '0'; 
    int colfim = entrada[4] - 'A';
    int linfim = entrada[5] - '0';
    // checagem da origem e do destino.
    if(ehposicaovalida(linin, colin) == 0) return 0;
    if(ehposicaovalida(linfim, colfim) == 0) return 0;
    //verifica a se a posicao de entrada eh uma casa vazia e se eh a vez do jogador.
    if(tabuleiro[linin][colin] == casa_vazia) return 0;
    
    if(jogadoratual == 'C' && tabuleiro[linin][colin] != cima_normal && tabuleiro[linin][colin] != cima_dama) return 0;
    if(jogadoratual == 'B' && tabuleiro[linin][colin] != baixo_normal && tabuleiro[linin][colin] != baixo_dama) return 0;
    
    if(tabuleiro[linfim][colfim] != casa_vazia) return 0;
    if(linin == linfim && colin == colfim) return 0;

    if(abs(linfim - linin) != abs(colfim - colin)) return 0;
    //Verificando se estamos jogando com alguma dama.
    if(tabuleiro[linin][colin] == cima_dama || tabuleiro[linin][colin] == baixo_dama){
        int passo_lin = (linfim > linin) ? 1 : -1;
        int passo_col = (colfim > colin) ? 1 : -1;

        int i = linin + passo_lin;
        int j = colin + passo_col;

        while(i != linfim){
            if(tabuleiro[i][j] != casa_vazia) return 0;
            i = i + passo_lin;
            j = j + passo_col;
        }
    }else{
        if(abs(linfim - linin) != 1) return 0;
        if(jogadoratual == 'C' && linfim < linin) return 0; // verificando se foi para frente ou para tras.
        if(jogadoratual == 'B' && linfim > linin) return 0;

    }
    
    
}

int ehposicaovalida(int lin, int col){
    if(lin >= 0 && lin <= tam_tabuleiro - 1 && col >= 0 && col <= tam_tabuleiro - 1){
        if((lin + col) % 2 == 1) return 1;
    }
    return 0;
}
void promoverpeca(char tabuleiro[tam_tabuleiro][tam_tabuleiro], int lin, int col){
    
}
