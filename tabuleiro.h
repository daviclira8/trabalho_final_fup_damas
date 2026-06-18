/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

#ifndef TABULEIRO_H
#define TABULEIRO_H

#define cima_normal 'o'
#define cima_dama 'O'
#define baixo_normal '@'
#define baixo_dama '&'
#define casa_invalida '#'
#define casa_vazia ' '

void inicializartabuleiro(char tabuleiro[10][10]);
void imprimirtabuleiro(char tabuleiro[10][10]);

#endif
