/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/
#include "tabuleiro.h"
#include "engine.h"
#include "captura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variaveis para contabilizar a quantidade de peças que faltam
int pecas_cima = 15;
int pecas_baixo = 15;

//Essa função será responsável por validar as jogadas, verificando a sintaxe e o formato da entrada, validando as coordenadas, as peças e as regras de movimento. 
//Declarar essas variaveis será util para transformar as entradas em algo legivel dentro de uma matriz 10x10.

int validar_jogada(char *entrada, char jogadoratual){
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
        if(abs(linfim - linin) != 1 && abs(linfim-linin) != 2) return 0;
        if(jogadoratual == 'C' && linfim < linin) return 0; // verificando se foi para frente ou para tras.
        if(jogadoratual == 'B' && linfim > linin) return 0;
    }

    /*
    Precisa fazer função para verificar se a peça está voltando para trás sem estar capturando outra
    */
    return 1; //Se passou por todas as checagens e não caiu em nenhum return 0, a jogada é válida!
    
}

int ehposicaovalida(int lin, int col){
    if(lin >= 0 && lin <= 10 - 1 && col >= 0 && col <= 10 - 1){
        if((lin + col) % 2 == 1) return 1;
    }
    return 0;
}
void promoverpeca(int lin, int col){
    if(tabuleiro[lin][col] == cima_normal && lin == 9){
        tabuleiro[lin][col] = cima_dama;
    }
    if(tabuleiro[lin][col] == baixo_normal && lin == 0){
        tabuleiro[lin][col] = baixo_dama;
    }
}

//função feita para processar jogada por jogada de modo a enxutar a int main
int jogada(char* entrada, char jogador){
    int coluna_inicial = entrada[0] - 'A';
    int linha_inicial = entrada[1] - '0';
    int coluna_final = entrada[4] - 'A';
    int linha_final = entrada[5] - '0';
    int i;
    struct captura jogada_ehcap_res = jogada_eh_captura(entrada);
    
    char peca_inicial = tabuleiro[linha_inicial][coluna_inicial];

    //primeiramente, será realizada a validação da jogada indicada
    if(validar_jogada(entrada, jogador) == 0){
        return 0;
    }
    if(captura_possivel(jogador) && jogada_ehcap_res.booleano != 1){
        return 0;
    }
    //após essas checkagens, temos certeza que a jogada indicada é válida, logo, nos resta modificar o tabuleiro

    for(i = 0; i < 10; i++){
        promoverpeca(0, i);
        promoverpeca(9,i);
    }
    if(jogada_ehcap_res.booleano == 1){
        //processamento de capturas
        if(peca_inicial == cima_normal || peca_inicial == baixo_normal){
            tabuleiro[(linha_final+linha_inicial)/2][(coluna_final+coluna_inicial)/2] = ' ';
            tabuleiro[linha_inicial][coluna_inicial] = ' ';
            tabuleiro[linha_final][coluna_final] = peca_inicial;
            if(peca_inicial == cima_normal) pecas_baixo--;
            else pecas_cima--;
            return 1;
        }
        else{
            tabuleiro[jogada_ehcap_res.linha_inimigo][jogada_ehcap_res.coluna_inimigo] = ' ';
            tabuleiro[linha_inicial][coluna_inicial] = ' ';
            tabuleiro[linha_final][coluna_final] = peca_inicial;
            if(peca_inicial == cima_dama) pecas_baixo--;
            else pecas_cima--;
            return 1;
        }
    }
    else{
        //processamento de jogadas normais
        tabuleiro[linha_inicial][coluna_inicial] = ' ';
        tabuleiro[linha_final][coluna_final] = peca_inicial;
        return 1;
    }
}