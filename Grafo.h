#ifndef GRAFO_H
#define GRAFO_H

#define MAX_ENIGMAS 10
#define MAX_VERTICES 100
#define MAX_ARESTAS 200
#define MAX_JOGADORES 100

typedef struct salaNarrativa {
    const char* nome;
    const char* narrativa;
    int enigmaID;
} SalaNarrativa;

typedef struct jogador {
    char nome[50];
    int pontuacao;
    double tempo;
} Jogador;

typedef struct vertice Vertice;
typedef struct aresta Aresta;
typedef struct grafo Grafo;
typedef struct inventario Inventario;
typedef struct ranking Ranking;

extern SalaNarrativa narrativaSalas[MAX_ENIGMAS];
extern const char* enigmas[MAX_ENIGMAS];
extern const char* opcoes[MAX_ENIGMAS][2];
extern int respostas[MAX_ENIGMAS];

void inicializarNarrativasEEnigmas(void);
Grafo* cria_Grafo(int max_vertices, int max_arestas);
void defineEnigma(Grafo* g, int vertice, const char* enigma, int pontuacao);
void defineOpcoesEnigma(Grafo* g, int vertice, const char* opcao1, const char* opcao2, int resposta_correta);
void insereAresta(Grafo* g, int origem, int destino, double peso, const char* descricao);
int* obterArestasSaida(Grafo* g, int vertice, int* quantidade);
void liberarGrafo(Grafo* g);
void setNumVertices(Grafo* g, int n);
void imprimirMapa(int salaAtual);
Inventario* criaInventario(void);
void tentarUsarItem(Inventario* inv, int* desbloqueou, int* pontuacao, int pontosSala);
void destruirInventario(Inventario* inv);
Ranking* criaRanking(void);
void rankingAdicionar(Ranking* r, const char* nome, int pontos, double tempo);
int compararJogadores(const void* a, const void* b);
void rankingOrdenar(Ranking* r);
void rankingExibir(Ranking* r);
void liberaRanking(Ranking* r);
int salaDesbloqueada(Grafo* g, int vertice);
void desbloquearSala(Grafo* g, int vertice);
const char* obterEnigma(Grafo* g, int vertice);
const char* obterOpcao1(Grafo* g, int vertice);
const char* obterOpcao2(Grafo* g, int vertice);
int obterRespostaCorreta(Grafo* g, int vertice);
int obterPontuacaoSala(Grafo* g, int vertice);
int obterDestinoAresta(Grafo* g, int arestaIndice);
const char* obterDescricaoAresta(Grafo* g, int arestaIndice);
int obterNumArestas(Grafo* g);

#endif // GRAFO_H
