/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

#ifndef captura_h
#define captura_h

extern char tabuleiro[10][10];
struct captura {
    int booleano;
    int linha_inimigo;
    int coluna_inimigo;
};

int captura_possivel (char);

struct captura jogada_eh_captura(char*);

#endif
