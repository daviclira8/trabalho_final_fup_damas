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
            printf("Assim está o tabuleiro atualmente:\n");
            imprimirtabuleiro(tabuleiro);
            printf("Lembre-se de utilizar o seguinte formato de entrada: <linha_inicial><coluna_inicial>--<linha_final><coluna_final>\n");
            printf("Agora eh a vez do jogador %c\nDigite a seguir a Jogada desejada: ", jogador);
            scanf("%s", &entrada);
            jogada(entrada, jogador);
            if(jogada == 0){
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
    
    FILE *arquivo = fopen(entrada, "rt");
    if(arquivo == NULL){ /*Verificação na leitura do arquivo*/                             
        printf("Erro na abertura de arquivo\n");
        return EXIT_FAILURE;
    }

    if(fgets(linha, sizeof(linha), arquivo) != NULL){ /*Lê a primeira linha para saber quem começa*/
        numero_linha++;

        linha[strcspn(linha, "\n")] = 0; /*Remove quebras de linha*/

        if(strcmp(linha, "C") == 0)
            turno_atual == 'C';
        else if(strcmp(linha, "B") == 0)
            turno_atual == 'B';
        else{
            printf("Formato inicial invalido\n");
            fclose(arquivo);
            return EXIT_FAILURE;
        }
    }

    printf("Tabuleiro inicial:\n");
    imprimirtabuleiro(tabuleiro);

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        numero_linha++;

        linha[strcspn(linha, "\n")] = 0;

        if(strlen(linha) == 0) /*Verifica se a linha está vazia*/
            continue;
        
        printf("Executando jogada de linha: %d, (Turno: %c)", numero_linha, turno_atual);

        if(validar_jogada(linha, turno_atual) == 0){
            printf("Jogada invalida na linha %d.\nFinalizando jogo!\n", numero_linha);
            fclose(arquivo);
            break;
        }
    }


}

