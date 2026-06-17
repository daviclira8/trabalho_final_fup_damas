/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/
#include "captura.h"
#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"



//a função a seguir percorrerá todo o tabuleiro e irá verificar se tem alguma captura disponível para o jogador da vez
//sendo o jogador de cima = 1 e o jogador de baixo = 2
//a função será como uma booleana, retornara 0 caso seja falso e retornando 1 caso exista alguma captura possível
//Possui uma lógica para peças normais, checkando suas diagonais de até 2 blocos de distancia
//para damas, percorre as diagonais todas, haja vista que suas movimentacoes sao diferentes
int captura_possivel(int jogador){
    int i, j, z;
    int passos, inimigo;
    int dir_i[4] = {1, 1, -1, -1};
    int dir_j[4] = {1, -1, 1, -1};
    int linha_atual;
    int coluna_atual;
    
    char peca_atual;

    //teste para o jogador de cima o qual as peças são 'o' e 'O'
    //sendo um tipo de teste para a peça normal e um para a dama haja vista que esta pode andar mais de um bloco de uma vez
    if(jogador == 1){
        for(i = 0; i < 10; i++){
            for(j = 0; j < 10; j++){
                if(tabuleiro[i][j] == 'o'){
                    if((tabuleiro[i+1][j+1] == '@' || tabuleiro[i+1][j+1] == '&') && tabuleiro[i+2][j+2] == ' '){
                        return 1;
                    }
                    else if((tabuleiro[i+1][j-1] == '@' || tabuleiro[i+1][j-1] == '&') && tabuleiro[i+2][j-2] == ' '){
                        return 1;
                    }
                    else if((tabuleiro[i-1][j+1] == '@' || tabuleiro[i-1][j+1] == '&') && tabuleiro[i-2][j+2] == ' '){
                        return 1;
                    }
                    else if((tabuleiro[i-1][j-1] == '@' || tabuleiro[i-1][j-1] == '&') && tabuleiro[i-2][j-2] == ' '){
                        return 1;
                    }
                }
                else if (tabuleiro[i][j] == 'O'){
                    for(z = 0; z < 4; z++){
                        passos = 1;
                        inimigo = 0;
                        while((i + (dir_i[z] * passos)) >= 0 && (i + (dir_i[z] * passos)) < 10){
                            if((j + (dir_j[z] * passos)) < 0 || (j + (dir_j[z] * passos)) >= 10) break;
                            
                            linha_atual = i + (dir_i[z] * passos);
                            coluna_atual = j + (dir_j[z] * passos);
                            peca_atual = tabuleiro[linha_atual][coluna_atual];

                            if(peca_atual == 'o' || peca_atual == 'O') break;

                            if(peca_atual == '@' || peca_atual == '&') inimigo++;

                            if(peca_atual == ' ' && inimigo == 1) return 1;

                            if(peca_atual == casa_invalida) break;

                            if(inimigo > 1) break;

                            passos++;
                        }
                    }

                }
            }
        }
    }
    //teste para o jogador de baixo o qual as peças são '@' e '&'
    //sendo um tipo de teste para a peça normal e um para a dama haja vista que esta pode andar mais de um bloco de uma vez
    else{
        for(i = 0; i < 10; i++){
            for(j = 0; j < 10; j++){
                if(tabuleiro[i][j] == '@'){
                    if((tabuleiro[i+1][j+1] == 'o' || tabuleiro[i+1][j+1] == 'O') && tabuleiro[i+2][j+2] == ' '){
                        return 1;
                    }
                    else if((tabuleiro[i+1][j-1] == 'o' || tabuleiro[i+1][j-1] == 'O') && tabuleiro[i+2][j-2] == ' '){
                        return 1;
                    }
                    else if((tabuleiro[i-1][j+1] == 'o' || tabuleiro[i-1][j+1] == 'O') && tabuleiro[i-2][j+2] == ' '){
                        return 1;
                    }
                    else if((tabuleiro[i-1][j-1] == 'o' || tabuleiro[i-1][j-1] == 'O') && tabuleiro[i-2][j-2] == ' '){
                        return 1;
                    }
                }
                else if (tabuleiro[i][j] == '&'){
                    for(z = 0; z < 4; z++){
                        passos = 1;
                        inimigo = 0;
                        while((i + (dir_i[z] * passos)) >= 0 && (i + (dir_i[z] * passos)) < 10){
                            if((j + (dir_j[z] * passos)) < 0 || (j + (dir_j[z] * passos)) >= 10) break;
                            
                            linha_atual = i + (dir_i[z] * passos);
                            coluna_atual = j + (dir_j[z] * passos);
                            peca_atual = tabuleiro[linha_atual][coluna_atual];

                            if(peca_atual == '@' || peca_atual == '&') break;

                            if(peca_atual == 'o' || peca_atual == 'O') inimigo++;

                            if(peca_atual == ' ' && inimigo == 1) return 1;

                            if(peca_atual == casa_invalida) break;

                            if(inimigo > 1) break;

                            passos++;
                        }
                    }

                }
            }
        }
    }
    return 0;
}

//a seguinte função processara se a jogada eh uma captura
//ela já é feita considerando que a jogada é uma jogada válida
//Essa função já processa a captura ao retirar a peça capturada do tabuleiro
//existe uma lógica para peças normais e uma para damas, haja vista que suas movimentações são diferentes
//na dama é feito um loop para percorrer a diagonal indicada para validar
//em peças normais basta checkar as 3 posicoes indicadas
int jogada_eh_captura(char* jogada){

    int linha_inicial = jogada[0] - 'A';
    int coluna_inicial = jogada[1] - '0';
    int linha_final = jogada[4] - 'A';
    int coluna_final = jogada[5] - '0';
    
    int inimigos = 0;

    int i, j;
    int passos = 1;

    int linha_peca_inimiga, coluna_peca_inimiga;

    char peca_inicial = tabuleiro[linha_inicial][coluna_inicial];
    char peca_meio = tabuleiro[(linha_final+linha_inicial)/2][(coluna_final+coluna_inicial)/2];
    char peca_final = tabuleiro[linha_final][coluna_final];
    char peca_atual;

    int linha_atual;
    int coluna_atual;

    if(peca_inicial == cima_normal){
        if((peca_meio == baixo_normal || peca_meio == baixo_dama) && peca_final == ' '){
            tabuleiro[(linha_final+linha_inicial)/2][(coluna_final+coluna_inicial)/2] = ' ';
            tabuleiro[linha_inicial][coluna_inicial] = ' ';
            tabuleiro[linha_final][coluna_final] = peca_inicial;
            return 1;
        }
    }
    else if(peca_inicial == cima_dama){
        passos = 1;
        inimigos = 0;

        if(linha_final - linha_inicial > 0) i = 1;
        else if (linha_final - linha_inicial < 0) i = -1;

        if(coluna_final - coluna_inicial > 0) j = 1;
        else if (coluna_final - coluna_inicial < 0) j = -1;

        linha_atual = linha_inicial + (i * passos);
        coluna_atual = coluna_inicial + (j * passos);

        while(linha_atual >= 0 && linha_atual < 10){
            if(coluna_atual < 0 || coluna_atual >= 10) break;
                            
            linha_atual = linha_inicial + (i * passos);
            coluna_atual = coluna_inicial + (j * passos);
            peca_atual = tabuleiro[linha_atual][coluna_atual];

            if(peca_atual == cima_dama || peca_atual == cima_normal) return 0;

            if(peca_atual == baixo_dama || peca_atual == baixo_normal){
                inimigos++;
                linha_peca_inimiga = linha_atual;
                coluna_peca_inimiga = coluna_atual;

            } 

            if(peca_atual == ' ' && inimigos == 1){
                if(linha_atual == linha_final && coluna_atual == coluna_final){
                    tabuleiro[linha_inicial][coluna_inicial] = ' ';
                    tabuleiro[linha_final][coluna_final] = peca_inicial;
                    tabuleiro[linha_peca_inimiga][coluna_peca_inimiga] = ' ';
                    return 1;
                }
            } 

            if(inimigos > 1) return 0;

            passos++;
        }
    }

    else if(peca_inicial == baixo_normal){
        if((peca_meio == cima_normal || peca_meio == cima_dama) && peca_final == ' '){
            tabuleiro[(linha_final+linha_inicial)/2][(coluna_final+coluna_inicial)/2] = ' ';
            tabuleiro[linha_inicial][coluna_inicial] = ' ';
            tabuleiro[linha_final][coluna_final] = peca_inicial;
            return 1;
        }
    }
    else{
        passos = 1;
        inimigos = 0;

        if(linha_final - linha_inicial > 0) i = 1;
        else if (linha_final - linha_inicial < 0) i = -1;

        if(coluna_final - coluna_inicial > 0) j = 1;
        else if (coluna_final - coluna_inicial < 0) j = -1;

        while(linha_atual >= 0 && linha_atual < 10){
            if(coluna_atual < 0 || coluna_atual >= 10) break;
                            
            linha_atual = linha_inicial + (i * passos);
            coluna_atual = coluna_inicial + (j * passos);
            peca_atual = tabuleiro[linha_atual][coluna_atual];

            if(peca_atual == baixo_dama || peca_atual == baixo_normal) return 0;;

            if(peca_atual == cima_dama || peca_atual == cima_normal){
                inimigos++;
                linha_peca_inimiga = linha_atual;
                coluna_peca_inimiga = coluna_atual;

            } 

            if(peca_atual == ' ' && inimigos == 1){
                if(linha_atual == linha_final && coluna_atual == coluna_final){
                    tabuleiro[linha_inicial][coluna_inicial] = ' ';
                    tabuleiro[linha_final][coluna_final] = peca_inicial;
                    tabuleiro[linha_peca_inimiga][coluna_peca_inimiga] = ' ';
                    return 1;
                }
            } 

            if(inimigos > 1) return 0;

            passos++;
        }
    }
    return 0;
}