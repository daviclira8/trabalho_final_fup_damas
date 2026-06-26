/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "tabuleiro.h"
#include "captura.h"

void modo_offline(char tab[10][10], const char *entrada); /*Chamada da função para abrir os arquivos*/

int main(int narg, char *argv[]){
    int i;
    char entrada[7];
    char jogador;
    int resultado;
    int invalido;
    
    if(narg == 1){
        inicializartabuleiro(tabuleiro);
        printf("Qual jogador irá comecar jogando?\nSendo B o de baixo e C o de cima\n");
        scanf("%c", &jogador);
        while(pecas_baixo > 0 && pecas_cima > 0){
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            if(invalido == 1){
                printf("Jogada invalida!\nTente novamente\n");
            }
            printf("Assim está o tabuleiro atualmente:\n");
            imprimirtabuleiro(tabuleiro);
            printf("Utilize as letras em maiusculo\n");
            printf("Lembre-se de utilizar o seguinte formato de entrada: <coluna_inicial><linha_inicial>--<coluna_final><linha_final>\n");
            printf("O jogador de cima ainda tem %d peca(s)\n", pecas_cima);
            printf("O jogador de baixo ainda tem %d peca(s)\n", pecas_baixo);
            printf("Agora eh a vez do jogador %c\nDigite a seguir a Jogada desejada: ", jogador);
            scanf("%s", entrada);
            resultado = jogada(entrada, jogador);
            invalido = 0;
            if(resultado == 0){
                invalido = 1;
                continue;
            }
            else{
                if(jogada_eh_captura(entrada).booleano){
                    continue;
                }
                else{
                    jogador = (jogador == 'B') ? 'C' : 'B';
                }
            }
        }
        
    }
    else{
        for(i = 0; i < narg; i++){
            inicializartabuleiro(tabuleiro);
            modo_offline(tabuleiro, argv[i]);
        }
    }
}

void modo_offline(char tab[10][10], const char *entrada){
    char linha[256];
    int numero_linha = 0;
    char turno_atual = ' ';
    int resultado;
    int captura;
    
    FILE *arquivo = fopen(entrada, "rt");
    if(arquivo == NULL){ /*Verificação na leitura do arquivo*/                             
        printf("Erro na abertura de arquivo: %s\n", entrada);
        return;
    }

    if(fgets(linha, sizeof(linha), arquivo) != NULL){ /*Lê a primeira linha para saber quem começa*/
        numero_linha++;

        linha[strcspn(linha, "\n")] = 0; /*Remove quebras de linha*/

        if(strcmp(linha, "C") == 0)
            turno_atual = 'C';
        else if(strcmp(linha, "B") == 0)
            turno_atual = 'B';
        else{
            printf("Formato inicial invalido\n");
            fclose(arquivo);
            return;
        }
    }

    printf("Tabuleiro inicial:\n");
    imprimirtabuleiro(); // CORRIGIDO: Sem passar parâmetro aqui

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        numero_linha++;

        linha[strcspn(linha, "\n")] = 0;

        if(strlen(linha) == 0) /*Verifica se a linha está vazia*/
            continue;
        
        printf("\n=========================================\n");
        printf("Executando jogada de linha: %d, (Turno: %c) -> %s\n", numero_linha, turno_atual, linha);

        captura = jogada_eh_captura(linha).booleano;
        resultado = jogada(linha, turno_atual);

        if(resultado == 0){
            printf("Jogada invalida na linha %d.\nFinalizando jogo!\n", numero_linha);
            fclose(arquivo);
            return;
        }

        imprimirtabuleiro(); // CORRIGIDO: Sem passar parâmetro aqui
        printf("Pecas restantes - Cima: %d | Baixo: %d\n", pecas_cima, pecas_baixo);

        if(captura == 1){
            printf("Foi uma captura! O turno continua com %c.\n", turno_atual);
            continue; 
        } else {
            turno_atual = (turno_atual == 'B') ? 'C' : 'B';
        }
    }

    fclose(arquivo);
}