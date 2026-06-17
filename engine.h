/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

#ifndef engine_h
#define engine_h
#include "tabuleiro.h"

#define tam_tabuleiro 10
//o typedef cria um apelido para um dado ja existente, para deixar o codigo mais legivel e facil de entender.
typedef struct{
    int lin, col;
} coordenada;
// Funções do integrante 2 (Roger)
int validar_jogada(char tabuleiro[tam_tabuleiro][tam_tabuleiro], char *entrada, char jogadoratual, int modojogo, int linha_artigo);
int ehposicaovalida(int lin, int col);
void promoverpeca(char tabuleiro[tam_tabuleiro][tam_tabuleiro], int lin, int col);

//Funções do integrante 3 que serão utéis ao código engine.c para a identificação de capturas possíveis.


#endif