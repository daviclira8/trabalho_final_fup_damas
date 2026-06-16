/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/
#include "validacao.h"
#include <stdio.h>
#include <stdlib.h>

//a função a seguir percorrerá todo o tabuleiro e irá verificar se tem alguma captura disponível para o jogador da vez
//sendo o jogador de cima = 1 e o jogador de baixo = 2

//a função será como uma booleana, retornara 0 caso seja falso e retornando 1 caso exista alguma captura possível
int captura_possivel(char** tabuleiro, int jogador){
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
        for(i = 2; i < 21; i+=2){
            for(j = 2; j < 21; j+=2){
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
                        while((i + (dir_i[z] * passos)) > 2 && (i + (dir_i[z] * passos)) < 20){
                            if((j + (dir_j[z] * passos)) < 2 && (j + (dir_j[z] * passos)) > 20) break;
                            
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
        for(i = 2; i < 21; i+=2){
            for(j = 2; j < 21; j+=2){
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
                        while((i + (dir_i[z] * passos)) > 2 && (i + (dir_i[z] * passos)) < 20){
                            if((j + (dir_j[z] * passos)) < 2 || (j + (dir_j[z] * passos)) > 20) break;
                            
                            linha_atual = i + (dir_i[z] * passos);
                            coluna_atual = j + (dir_j[z] * passos);
                            peca_atual = tabuleiro[linha_atual][coluna_atual];

                            if(peca_atual == '@' || peca_atual == '&') break;

                            if(peca_atual == 'o' || peca_atual == 'O') inimigo++;

                            if(peca_atual == ' ' && inimigo == 1) return 1;

                            if(inimigo > 1) return 0;

                        }
                    }

                }
            }
        }
    }
    return 0;
}
