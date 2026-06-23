/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

#ifndef engine_h
#define engine_h

extern int pecas_cima = 15;
extern int pecas_baixo = 15;

extern char tabuleiro[10][10];
extern struct captura{
    int booleano;
    int linha_inimigo;
    int coluna_inimigo;
};


// Funções do integrante 2 (Roger)
int validar_jogada(char*, char);
int ehposicaovalida(int, int);
void promoverpeca(int, int);

void jogada(char*, char);

//Funções do integrante 3 que serão utéis ao código engine.c para a identificação de capturas possíveis.


#endif