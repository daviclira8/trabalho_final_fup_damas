/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"


char tabuleiro[10][10]; // tabuleiro como variável global
//Conversar com o sasaki sobre a linha 18, acredito que em vez de 0, seja 1.
void inicializartabuleiro(char tabuleiro[10][10]){ // função que inicializa o tabuleiro
    int i, j;
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            if((i + j) % 2 == 0){
                if(i <= 2){
                    tabuleiro[i][j] = cima_normal;
                }else if(i >= 7){
                    tabuleiro[i][j] = baixo_normal;
                }else{
                    tabuleiro[i][j] = casa_vazia;
                }
            }else{
                tabuleiro[i][j] = casa_invalida;
            }
        }
    }
}



void imprimirtabuleiro(char tabuleiro[10][10]){
    int i, j;
    printf("  A B C D E F G H I J\n");
    for(i = 0; i < 10; i++){
        printf(" +-+-+-+-+-+-+-+-+-+-+\n");
        printf("%d|", i);
        for(j = 0; j < 10; j++){
            printf("%c|", tabuleiro[i][j]);
        }
        printf("%d\n", i);    
    }
    printf(" +-+-+-+-+-+-+-+-+-+-+\n");
    printf("  A B C D E F G H I J\n");
}