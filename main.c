#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Grafo.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));

    inicializarNarrativasEEnigmas();

    Jogador jogadores[MAX_JOGADORES];
    int totalJogadores = 0, repetir;

    do {
        Grafo* grafo = cria_Grafo(10, 30);
        Inventario* inv = criaInventario();
        char nome[50];

        printf("\n\033[1;35m=== Bem-vindo ao jogo Ecos do Passado ===\033[0m\n");
        printf("Digite seu nome, aventureiro: ");
        scanf("%49s", nome);

        for (int i = 0; i < 10; i++) {
            int id = narrativaSalas[i].enigmaID;
            defineEnigma(grafo, i, enigmas[id], 10 + rand() % 10);
            defineOpcoesEnigma(grafo, i, opcoes[id][0], opcoes[id][1], respostas[id]);
        }
        setNumVertices(grafo, 10);

        insereAresta(grafo, 0, 1, 1.0, "Passagem Escura para Biblioteca");
        insereAresta(grafo, 0, 5, 1.0, "Escada Escondida para o Conselho");
        insereAresta(grafo, 1, 2, 1.0, "Porta Oculta para Espelhos");
        insereAresta(grafo, 1, 6, 1.0, "Corredor Secreto para Jardim");
        insereAresta(grafo, 2, 3, 1.0, "Porta de Ferro para Ferreiro");
        insereAresta(grafo, 2, 4, 1.0, "Escada Espiral para Torre");
        insereAresta(grafo, 5, 6, 1.0, "Porta Lateral para Jardim");
        insereAresta(grafo, 6, 7, 1.0, "Alameda Sombria para Santuário");
        insereAresta(grafo, 7, 8, 1.0, "Passagem Secreta para Passagem");
        insereAresta(grafo, 8, 9, 1.0, "Escadaria Final para o Trono");

        int pontuacao = 0, sala = 0, erros = 0;
        time_t ini = time(NULL);

        while (1) {
            printf("\n\033[1;34m=== Sala %d: %s ===\033[0m\n\033[0;36m%s\033[0m\n",
                   sala, narrativaSalas[sala].nome, narrativaSalas[sala].narrativa);

            printf("1. Avançar | 2. Usar Item | 3. Ver Mapa | 0. Sair\nEscolha: ");
            int opcao;
            scanf("%d", &opcao);

            if (opcao == 0) break;

            if (opcao == 2) {
                int desbloqueou = salaDesbloqueada(grafo, sala);
                tentarUsarItem(inv, &desbloqueou, &pontuacao, obterPontuacaoSala(grafo, sala));
                if (desbloqueou) desbloquearSala(grafo, sala);
                continue;
            }

            if (opcao == 3) {
                imprimirMapa(sala);
                printf("Você está na Sala [%d] - %s\n", sala, narrativaSalas[sala].nome);
                continue;
            }

            if (!salaDesbloqueada(grafo, sala)) {
                printf("\n\033[1;36mEnigma: %s\033[0m\n1 - %s\n2 - %s\n",
                       obterEnigma(grafo, sala), obterOpcao1(grafo, sala), obterOpcao2(grafo, sala));
                int r; scanf("%d", &r);
                if (r == obterRespostaCorreta(grafo, sala)) {
                    printf("\033[1;32m✅ Correto! Você ganhou %d pontos!\033[0m\n", obterPontuacaoSala(grafo, sala));
                    pontuacao += obterPontuacaoSala(grafo, sala);
                    desbloquearSala(grafo, sala);
                    erros = 0;
                } else {
                    erros++;
                    printf("\033[1;31m❌ Errado! Tentativas restantes: %d\033[0m\n", 3 - erros);
                    if (erros >= 3) {
                        printf("\n\033[1;31mGAME OVER\033[0m\n");
                        break;
                    }
                    continue;
                }
            }

            int qtd;
            int* saidas = obterArestasSaida(grafo, sala, &qtd);
            if (qtd == 0) break;

            printf("\n\033[1;33mPara onde deseja ir?\033[0m\n");
            for (int i = 0; i < qtd; i++) {
                int arestaIndex = saidas[i];
                int destino = obterDestinoAresta(grafo, arestaIndex);
                const char* descricao = obterDescricaoAresta(grafo, arestaIndex);
                printf("%d - %s (Sala %d - %s)\n",
                       i + 1,
                       descricao,
                       destino,
                       narrativaSalas[destino].nome);
            }

            int esc;
            printf("Escolha: ");
            scanf("%d", &esc);
            if (esc < 1 || esc > qtd) {
                free(saidas);
                continue;
            }

            sala = obterDestinoAresta(grafo, saidas[esc - 1]);
            free(saidas);

            if (sala == 9) {
                printf("\033[1;32m🏆 Você alcançou o Trono! Vitória! 🏆\033[0m\n");
                break;
            }
        }

        time_t fim = time(NULL);
        jogadores[totalJogadores].pontuacao = pontuacao;
        jogadores[totalJogadores].tempo = difftime(fim, ini);
        strcpy(jogadores[totalJogadores].nome, nome);
        totalJogadores++;

        liberarGrafo(grafo);
        destruirInventario(inv);

        printf("\nJogar novamente? (1 - Sim / 0 - Não): ");
        scanf("%d", &repetir);

    } while (repetir && totalJogadores < MAX_JOGADORES);

    qsort(jogadores, totalJogadores, sizeof(Jogador), compararJogadores);

    printf("\n=== Ranking dos Aventureiros ===\n");
    for (int i = 0; i < totalJogadores && i < 3; i++) {
        printf("%d) %s - %d pontos - %.0f segundos\n",
               i + 1, jogadores[i].nome, jogadores[i].pontuacao, jogadores[i].tempo);
    }

    return 0;
}
