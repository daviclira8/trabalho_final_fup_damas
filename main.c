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

void modo_offline(const char *entrada); /*Chamada da função para abrir os arquivos*/

int main(int narg, char *argv[]){
    int i, resultado, invalido, captura;
    char entrada[7];
    char jogador;
        
    if(narg == 1){
        i=1;
        //loop p ficar jogando até o usuario indicar que não.
        while(i == 1){
            //inicialização de variaveis 
            pecas_baixo = 15;
            pecas_cima = 15;
            inicializartabuleiro(tabuleiro);
            jogador = ' ';
            while(jogador != 'B' && jogador != 'C'){
                printf("Qual jogador ira comecar jogando?\nSendo B o de baixo e C o de cima\n");
                scanf(" %c", &jogador);
            }
            while(pecas_baixo > 0 && pecas_cima > 0){
                //checkagem se existe jogada valida
                if(existe_jogada_valida(jogador) == 0){
                    if(jogador == 'B'){
                        pecas_baixo = 0;
                        continue;
                    }
                    else{
                        pecas_cima = 0;
                        continue;
                    }
                }
                //limpeza do terminal de modo a dispor somente o estado atual do tabuleiro
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                //checkagem de jogada invalida
                if(invalido == 1){
                    printf("Jogada invalida.\n");
                }

                printf("Assim esta o tabuleiro atualmente:\n");
                imprimirtabuleiro();
                printf("Utilize as letras em maiusculo\n");
                printf("Lembre-se de utilizar o seguinte formato de entrada: <coluna_inicial><linha_inicial>--<coluna_final><linha_final>\n");
                printf("O jogador de cima ainda tem %d peca(s)\n", pecas_cima);
                printf("O jogador de baixo ainda tem %d peca(s)\n", pecas_baixo);
                printf("Agora eh a vez do jogador %c\nDigite a seguir a Jogada desejada: ", jogador);
                scanf("%s", entrada);

                //processamento da entrada
                captura = jogada_eh_captura(entrada).booleano;
                resultado = jogada(entrada, jogador);
                invalido = 0;
                //processamento do turno de cada jogador
                if(resultado == 0){
                    invalido = 1;
                    continue;
                }
                else{
                    if(captura == 1){
                        continue;
                    }
                    else{
                        jogador = (jogador == 'B') ? 'C' : 'B';
                    }
                }
            }
            //processamento do vencedor
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            imprimirtabuleiro();
            if(pecas_baixo == 0){
                printf("O jogador de Cima foi o vencedor!\n");
                printf("Caso queiram jogar novamente, digitem 1, caso não queiram digitem 0: ");
                scanf("%d", &i);
            }
            else{
                printf("O jogador de Baixo foi o vencedor!\n");
                printf("Caso queiram jogar novamente, digitem 1, caso não queiram digitem 0: ");
                scanf("%d", &i);
            }
        }
    }
    else{
        for(i = 1; i < narg; i++){
            inicializartabuleiro(tabuleiro);
            modo_offline(argv[i]);
        }
    }
}


void modo_offline(const char *entrada){
    // Definições das variáveis
    char linha[256];
    int numero_linha = 0;
    char turno_atual = ' ';
    int resultado;
    int captura;
    pecas_baixo = 15;
    pecas_cima = 15;
    
    FILE *arquivo = fopen(entrada, "rt");
    if(arquivo == NULL){                         
        printf("Erro na abertura de arquivo: %s\n", entrada);
        return;
    }


    if(fgets(linha, sizeof(linha), arquivo) != NULL){ /*Lê a primeira linha para saber quem começa*/
        numero_linha++;

        linha[strcspn(linha, "\r\n")] = 0; /* Remove quebras de linha*/

        if(strcmp(linha, "C") == 0)
            turno_atual = 'C';
        else if(strcmp(linha, "B") == 0)
            turno_atual = 'B';
        else{
            printf("Jogador inicial inválido.\n");
            fclose(arquivo);
            return;
        }
    }

    /*Lê todas as linhas de jogadas do arquivo de entrada */
    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        numero_linha++;

        linha[strcspn(linha, "\r\n")] = 0;

        if(strlen(linha) == 0) /* Ignora linhas vazias */
            continue;
        

        // - Executa a jogada com a função jogada
        resultado = jogada(linha, turno_atual);

        /* - Caso a jogada seja inválida, exibe a mensagem e dá continue */
        if(resultado == 0){
            printf("Jogada invalida na linha %d do arquivo de entrada.\n", numero_linha);
            continue;
        }

        // Verifica se é captura
        captura = jogada_eh_captura(linha).booleano;

        /* Alterna o turno apenas se não foi captura */
        if(captura == 1){
            // Se foi captura obrigatória realizada com sucesso, o turno continua com o mesmo jogador
            continue; 
        } else {
            turno_atual = (turno_atual == 'B') ? 'C' : 'B';
        }
    }

    fclose(arquivo);

    /* Após processar todo o arquivo, exibe a situação final do tabuleiro */
    imprimirtabuleiro();
    
    // Calcula as peças capturadas com base no que restou no tabuleiro
    int capturadas_por_cima = 15 - pecas_baixo;
    int capturadas_por_baixo = 15 - pecas_cima;
    printf("Cima = %d / Baixo = %d\n", capturadas_por_cima, capturadas_por_baixo);

    /* Determina se algum jogador venceu a partida */
    if (pecas_cima == 0) {
        printf("O vencedor é o usuário de BAIXO.\n");
    } else if (pecas_baixo == 0) {
        printf("O vencedor é o usuário de CIMA.\n");
    }
}