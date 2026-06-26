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
    int i;
    char entrada[7];
    char jogador;
    int resultado;
    int invalido;
    int captura;
    
    if(narg == 1){
        inicializartabuleiro(tabuleiro);
        printf("Qual jogador ira comecar jogando?\nSendo B o de baixo e C o de cima\n");
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
            printf("Assim esta o tabuleiro atualmente:\n");
            imprimirtabuleiro(tabuleiro);
            printf("Utilize as letras em maiusculo\n");
            printf("Lembre-se de utilizar o seguinte formato de entrada: <coluna_inicial><linha_inicial>--<coluna_final><linha_final>\n");
            printf("O jogador de cima ainda tem %d peca(s)\n", pecas_cima);
            printf("O jogador de baixo ainda tem %d peca(s)\n", pecas_baixo);
            printf("Agora eh a vez do jogador %c\nDigite a seguir a Jogada desejada: ", jogador);
            scanf("%s", entrada);
            captura = jogada_eh_captura(entrada).booleano;
            resultado = jogada(entrada, jogador);
            invalido = 0;
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
        /*
        Mostrar tabuleiro final e vencedor
        */
        
    }
    else{
        for(i = 0; i < narg; i++){
            inicializartabuleiro(tabuleiro);
            modo_offline(argv[i]);
        }
    }
}

void modo_offline(const char *entrada){
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
    imprimirtabuleiro();

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        numero_linha++;

        linha[strcspn(linha, "\n")] = 0;

        if(strlen(linha) == 0) /*Verifica se a linha está vazia*/
            continue;
        
        printf("\n=========================================\n");
        printf("Executando jogada de linha: %d, (Turno: %c) -> %s\n", numero_linha, turno_atual, linha);

        // 1. Guarda se a jogada pretendida é uma captura antes de processar
        captura = jogada_eh_captura(linha).booleano;

        // 2. Executa a jogada através do motor de jogo (valida e atualiza a matriz do tabuleiro)
        resultado = jogada(linha, turno_atual);

        if(resultado == 0){
            printf("Jogada invalida detectada na linha %d do arquivo.\nFinalizando jogo offline!\n", numero_linha);
            fclose(arquivo);
            return;
        }

        // 3. Imprime o tabuleiro atualizado após o movimento bem-sucedido
        imprimirtabuleiro();
        printf("Pecas restantes - Cima: %d | Baixo: %d\n", pecas_cima, pecas_baixo);

        // 4. Alterna o turno baseado nas regras definidas por vocês no modo online
        if(captura == 1){
            printf("Foi uma captura! O turno continua com o jogador %c.\n", turno_atual);
            // Segue a lógica da sua main: se houver mais capturas subsequentes no arquivo,
            // o turno continuará pertencendo a ele na próxima linha.
            continue; 
        } else {
            turno_atual = (turno_atual == 'B') ? 'C' : 'B';
        }
    }

    printf("\n=========================================\n");
    printf("Fim do arquivo alcancado com sucesso!\n");
    
    // 5. Determinar o vencedor no fim do arquivo se um dos lados perdeu tudo
    if (pecas_cima == 0) {
        printf("O jogador de BAIXO (B) venceu!\n");
    } else if (pecas_baixo == 0) {
        printf("O jogador de CIMA (C) venceu!\n");
    } else {
        printf("Partida interrompida ou incompleta no arquivo.\n");
    }

    fclose(arquivo);
}
