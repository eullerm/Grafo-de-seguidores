#include "grafo.h"

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade) {
    TGrafo *vertice = (TGrafo *) malloc(sizeof(TGrafo));
    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->prox = g;
    vertice->vizinho = NULL;
    return vertice;
}

TGrafo *busca_vertice(TGrafo *vertice, char *nome) {
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0)) {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome) {
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0)) {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino) {
    TGrafo *vertice = busca_vertice(g, nome_origem);
    TVizinho *vizinho = (TVizinho *) malloc(sizeof(TVizinho));
    strcpy(vizinho->nome, nome_destino);
    vizinho->prox = vertice->vizinho;
    vertice->vizinho = vizinho;
}

void imprime(TGrafo *vertice) {
    while (vertice != NULL) {
        printf("Pessoa: %s - %d anos\n", vertice->nome, vertice->idade);
        printf("Segue: ");
        TVizinho *vizinho = vertice->vizinho;
        while (vizinho != NULL) {
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
        }
        printf("\n\n");
        vertice = vertice->prox;
    }
}

int numero_seguidos(TGrafo *g, char *nome) {

    if(!g) return 0;

    TGrafo *aux = g;
    aux = busca_vertice(aux, nome);

    //Checa se existe o nome no grafo.
    if(!aux) return 0;
    else{
        int i = 0;
        //Conta todos os vizinhos.
        while(aux->vizinho){
            i++;
            aux->vizinho = aux->vizinho->prox;
        }
        return i;
    }
}

int seguidores(TGrafo *vertice, char *nome, int imprime) {


    if(!vertice) return 0;
    else {
        TGrafo *aux = busca_vertice(vertice, nome);
        //Checa se existe a pessoa escolhida no grafo.
        if (!aux) return 0;
        else {
            aux = vertice;
            TVizinho *checa;
            int cont = 0;
            //Se a flag for positiva já da o print inicial para dizer quais são os seguidores.
            if (imprime==1) printf("Seguidores de %s: ", nome);

            while(aux){
                //Verifica se o vertice aponta para o nome passado pela função
                checa = busca_vizinho(aux->vizinho, nome);
                if(checa && strcmp(nome, checa->nome)==0){
                    if(imprime==1) printf("%s ", aux->nome);
                    cont++;
                }
                //Pula para o proximo vertice.
                aux = aux->prox;
            }
            printf("\n");
            return cont;
        }
    }
}

TGrafo *mais_popular(TGrafo *g) {
    if(!g) return NULL;
    else{
        int cont = 0;
        int cont2 = 0;
        TGrafo *aux = g;
        TGrafo *aux2 = g;
        TGrafo *tmp = g;
        TVizinho *contaVizinhos;
        while(aux){
            while(aux2){
                if (aux2!=aux) {
                    //Procura no vertice aux2 se ele tem conexão com o aux
                    contaVizinhos = busca_vizinho(aux2->vizinho, aux->nome);
                    if (contaVizinhos) cont++;
                }
                aux2 = aux2->prox;
            }
            //Armazena o mais popular
            if (cont>cont2){
                cont2 = cont;
                tmp = aux;
            }
            cont = 0;
            aux = aux->prox;
            aux2 = g;
        }
        return tmp;
    }
}

int segue_mais_velho(TGrafo *g, int imprime) {

    if(!g) return 0;
    else{
        TGrafo *aux = g;
        TGrafo *aux2;
        TGrafo *tmp = g;
        TVizinho *verificaVizinhos = g->vizinho;
        int cont = 0;
        int cont2 = 0;
        while(aux) {
            while (verificaVizinhos) {
                //Busca o vertice que tem conexão com aux
                aux2 = busca_vertice(g, verificaVizinhos->nome);
                if(aux2->idade > aux->idade) cont++;
                verificaVizinhos = verificaVizinhos->prox;
            }

            if (cont > cont2){
                cont2 = cont;
                //Só armazena o caso a variavel seja verdadeira.
                if(imprime==1) tmp = aux;
            }
            cont = 0;
            if(aux->prox) verificaVizinhos = aux->prox->vizinho;
            aux = aux->prox;
        }

        if(imprime==1){
            printf("%s segue: ", tmp->nome);
            while(tmp->vizinho){
                printf("%s ", tmp->vizinho->nome);
                tmp->vizinho = tmp->vizinho->prox;
            }
        }

        return cont2;
    }
}

void libera_vizinho(TVizinho *vizinho) {
    if (vizinho != NULL) {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TGrafo *vertice) {
    if (vertice != NULL) {
        libera_vizinho(vertice->vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}