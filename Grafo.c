#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

struct vertice {
    char enigma[256];
    char opcao1[100];
    char opcao2[100];
    int resposta_correta;
    int chave;
    int pontuacao;
};

struct aresta {
    int origem;
    int destino;
    double peso;
    char descricao[100];
};

struct grafo {
    int max_vertices;
    int max_arestas;
    int num_vertices;
    int num_arestas;
    Vertice vertices[MAX_VERTICES];
    Aresta arestas[MAX_ARESTAS];
};

struct inventario {
    int chaveMestra;
};

struct ranking {
    Jogador jogadores[MAX_JOGADORES];
    int total;
};

SalaNarrativa narrativaSalas[MAX_ENIGMAS] = {
    {"Calabouço Gelado", "Você acorda em uma cela úmida...", 0},
    {"Biblioteca Esquecida", "Livros proibidos sussurram segredos...", 1},
    {"Salão dos Espelhos", "Reflexos se deformam nas superfícies quebradas...", 2},
    {"Câmara do Ferreiro", "Martelos ecoam memórias de armas forjadas...", 3},
    {"Torre da Feiticeira", "Corvos observam seus passos silenciosos...", 4},
    {"Sala do Conselho", "Cadeiras vazias julgam seus segredos...", 5},
    {"Jardim Interno", "Folhas mortas contam histórias sombrias...", 6},
    {"Santuário Sombrio", "Vitrais rachados deixam a lua invadir...", 7},
    {"Passagem Secreta", "Corredores estreitos testam sua coragem...", 8},
    {"Salão do Trono", "O trono espera seu novo governante...", 9}
};

const char* enigmas[MAX_ENIGMAS] = {
    "Não posso ser visto, mas posso derrubar muralhas. O que sou?",
    "Sou leve como uma pena, mas ninguém consegue me segurar por muito tempo. O que sou?",
    "Acompanho você à noite, mas sumo no escuro. O que sou?",
    "Quanto mais tiro, mais deixo para trás. O que sou?",
    "Sigo você em todo lugar, mas não deixo rastros. O que sou?",
    "Posso encher uma sala sem ocupar espaço. O que sou?",
    "Passa na frente do sol sem fazer sombra. O que é?",
    "Posso voar sem asas e chorar sem olhos. O que sou?",
    "Sou a única coisa que aumenta quando é dividida. O que sou?",
    "O que quebra e não faz barulho?"
};

const char* opcoes[MAX_ENIGMAS][2] = {
    {"Vento", "Sombra"},
    {"Respiração", "Tempo"},
    {"Estrela", "Sombra"},
    {"Pegadas", "Buraco"},
    {"Sombra", "Ar"},
    {"Luz", "Som"},
    {"Vento", "Raio de luz"},
    {"Nuvem", "Vento"},
    {"Amor", "Fome"},
    {"Silêncio", "Vento"}
};

int respostas[MAX_ENIGMAS] = {1, 1, 2, 1, 1, 1, 1, 1, 1, 1};

void inicializarNarrativasEEnigmas(void) {}

Grafo* cria_Grafo(int max_vertices, int max_arestas) {
    Grafo* g = malloc(sizeof(Grafo));
    if (!g) return NULL;
    g->max_vertices = max_vertices;
    g->max_arestas = max_arestas;
    g->num_vertices = 0;
    g->num_arestas = 0;
    return g;
}

void defineEnigma(Grafo* g, int vertice, const char* enigma, int pontuacao) {
    strncpy(g->vertices[vertice].enigma, enigma, sizeof(g->vertices[vertice].enigma) - 1);
    g->vertices[vertice].pontuacao = pontuacao;
}

void defineOpcoesEnigma(Grafo* g, int vertice, const char* opcao1, const char* opcao2, int resposta_correta) {
    strncpy(g->vertices[vertice].opcao1, opcao1, sizeof(g->vertices[vertice].opcao1) - 1);
    strncpy(g->vertices[vertice].opcao2, opcao2, sizeof(g->vertices[vertice].opcao2) - 1);
    g->vertices[vertice].resposta_correta = resposta_correta;
}

void insereAresta(Grafo* g, int origem, int destino, double peso, const char* descricao) {
    if (g->num_arestas >= g->max_arestas) return;
    g->arestas[g->num_arestas].origem = origem;
    g->arestas[g->num_arestas].destino = destino;
    g->arestas[g->num_arestas].peso = peso;
    strncpy(g->arestas[g->num_arestas].descricao, descricao, sizeof(g->arestas[g->num_arestas].descricao) - 1);
    g->num_arestas++;
}

int* obterArestasSaida(Grafo* g, int vertice, int* quantidade) {
    int* saidas = malloc(sizeof(int) * g->num_arestas);
    int count = 0;
    for (int i = 0; i < g->num_arestas; i++)
        if (g->arestas[i].origem == vertice) saidas[count++] = i;
    *quantidade = count;
    return saidas;
}

void liberarGrafo(Grafo* g) {
     free(g);
}

void setNumVertices(Grafo* g, int n) {
     g->num_vertices = n;
}

Inventario* criaInventario(void) {
    Inventario* inv = malloc(sizeof(Inventario));
    inv->chaveMestra = 1;
    return inv;
}

void tentarUsarItem(Inventario* inv, int* desbloqueou, int* pontuacao, int pontosSala) {
    if (inv->chaveMestra) {
        printf("\033[1;32m🔑 Você usou a chave mestra para desbloquear a sala!\033[0m\n");
        *desbloqueou = 1;
        inv->chaveMestra = 0;
    } else {
        printf("\033[1;31m❌ Você não tem itens utilizáveis.\033[0m\n");
    }
}

void destruirInventario(Inventario* inv) {
    free(inv);
}

int salaDesbloqueada(Grafo* g, int vertice) {
    return g->vertices[vertice].chave;
}

void desbloquearSala(Grafo* g, int vertice) {
    g->vertices[vertice].chave = 1;
}

const char* obterEnigma(Grafo* g, int vertice) {
    return g->vertices[vertice].enigma;
}
const char* obterOpcao1(Grafo* g, int vertice) {
    return g->vertices[vertice].opcao1;
}
const char* obterOpcao2(Grafo* g, int vertice) {
    return g->vertices[vertice].opcao2;
}
int obterRespostaCorreta(Grafo* g, int vertice) {
    return g->vertices[vertice].resposta_correta;
}
int obterPontuacaoSala(Grafo* g, int vertice) {
    return g->vertices[vertice].pontuacao;
}

int obterDestinoAresta(Grafo* g, int i) {
    return g->arestas[i].destino;
}
const char* obterDescricaoAresta(Grafo* g, int i) {
    return g->arestas[i].descricao;
}

void imprimirMapa(int salaAtual) {
    printf("\n\033[1;36m=== MAPA DO LABIRINTO ===\033[0m\n");
    printf("[0] Calabouço --- [1] Biblioteca --- [2] Espelhos\n");
    printf("   |                    |               |\n");
    printf("[5] Conselho --- [6] Jardim --- [7] Santuário --- [8] Passagem --- [9] Trono\n");
    printf("                      |\n");
    printf("                  [3] Ferreiro\n");
    printf("                      |\n");
    printf("                  [4] Torre\n");
    printf("Você está na sala [%d]\n\n", salaAtual);
}

int compararJogadores(const void* a, const void* b) {
    const Jogador* ja = (const Jogador*)a;
    const Jogador* jb = (const Jogador*)b;
    if (ja->pontuacao != jb->pontuacao)
        return jb->pontuacao - ja->pontuacao;
    return (ja->tempo < jb->tempo) ? -1 : (ja->tempo > jb->tempo);
}
