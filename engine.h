/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

#ifndef engine_h
#define engine_h

extern int pecas_cima;
extern int pecas_baixo;

extern char tabuleiro[10][10];

extern struct captura jogada_ehcap_res;

// Funções do integrante 2 (Roger)
int validar_jogada(char*, char);
int ehposicaovalida(int, int);
void promoverpeca(int, int);

int jogada(char*, char);
int existe_jogada_valida(char);

#endif