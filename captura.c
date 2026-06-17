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
                        while((i + (dir_i[z] * passos)) > 0 && (i + (dir_i[z] * passos)) < 10){
                            if((j + (dir_j[z] * passos)) < 0 && (j + (dir_j[z] * passos)) > 10) break;
                            
                            linha_atual = i + (dir_i[z] * passos);
                            coluna_atual = j + (dir_j[z] * passos);
                            peca_atual = tabuleiro[linha_atual][coluna_atual];

                            if(peca_atual == 'o' || peca_atual == 'O') break;

                            if(peca_atual == '@' || peca_atual == '&') inimigo++;

                            if(peca_atual == ' ' && inimigo == 1) return 1;

                            if(inimigo > 1) return 0;

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
                        while((i + (dir_i[z] * passos)) > 0 && (i + (dir_i[z] * passos)) < 10){
                            if((j + (dir_j[z] * passos)) < 0 || (j + (dir_j[z] * passos)) > 10) break;
                            
                            linha_atual = i + (dir_i[z] * passos);
                            coluna_atual = j + (dir_j[z] * passos);
                            peca_atual = tabuleiro[linha_atual][coluna_atual];

                            if(peca_atual == '@' || peca_atual == '&') break;

                            if(peca_atual == 'o' || peca_atual == 'O') inimigo++;

                            if(peca_atual == ' ' && inimigo == 1) return 1;

                            if(peca_atual == casa_invalida) break;

                            if(inimigo > 1) return 0;
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
int jogada_eh_captura(char* jogada){
    int linha_inicial = jogada[0] - 'A';
    int coluna_inicial = jogada[1] - '0';
    int linha_final = jogada[4] - 'A';
    int coluna_final = jogada[5] - '0';
    
    int inimigos = 0;

    int i, j, z;
    int dir_i[4] = {1, 1, -1, -1};
    int dir_j[4] = {1, -1, 1, -1};
    int passos = 1;

    char peca_inicial = tabuleiro[linha_inicial][coluna_inicial];

    char peca_meio = tabuleiro[(linha_final+linha_inicial)/2][(coluna_final+coluna_inicial)/2];
    char peca_final = tabuleiro[linha_final][coluna_final];


    if(peca_inicial == cima_normal){
        if((peca_meio == baixo_normal || peca_meio == baixo_dama) && peca_final == ' '){
            tabuleiro[(linha_final+linha_inicial)/2][(coluna_final+coluna_inicial)/2] = ' ';
            tabuleiro[linha_inicial][coluna_inicial] = ' ';
            tabuleiro[linha_final][coluna_final] = peca_inicial;
            return 1;
        }
    }
}