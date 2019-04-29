#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho {
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo {
    char nome[10];
    int idade;
    TVizinho *vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade);

TGrafo *busca_vertice(TGrafo *vertice, char *nome);

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome);

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino);

void imprime(TGrafo *vertice);

int numero_seguidos(TGrafo *g, char *nome);

TGrafo *mais_popular(TGrafo *g);

int segue_mais_velho(TGrafo *g, int imprime);

void libera_vizinho(TVizinho *vizinho);

void libera_vertice(TGrafo *vertice);

#endif //GRAFO_GRAFO_H