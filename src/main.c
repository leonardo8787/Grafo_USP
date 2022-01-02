#include<stdio.h>
#include<stdlib.h>


typedef struct vizinho {
    int id_vizinho;
    struct vizinho *prox;
}TVizinho;

typedef struct grafo {
    int id_vertice;
    TVizinho *prim_vizinho;
    struct grafo *prox;
}TGrafo;

TGrafo *inicializa() {
    return NULL;
}

//impressão do grafo 
void imprime(TGrafo *g){
    while(g != NULL){
        printf("Vértice %d\n", g->id_vertice);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;
        while(v != NULL){
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}

//liberação da estrutura 
void libera(TGrafo *g){
    while(g != NULL){
        libera_vizinhos(g->prim_vizinho);
        TGrafo *temp = g;
        g = g->prox;
        free(temp);
    }
}

void libera_vizinhos(TVizinho *v){
    while(v != NULL){
        TVizinho *temp = v;
        v = v->prox;
        free(temp);
    }
}

//busca por vértice x 
TGrafo* busca_vertice(TGrafo* g, int x){
    while((g != NULL) && (g->id_vertice != x)){
        g = g->prox;
    }
    return g;
}

//busca por aresta (v1,v2) ou {v1, v2}
TVizinho* busca_aresta(TGrafo *g, int v1, int v2){
    TGrafo *pv1 = busca_vertice(g, v1);
    TGrafo *pv2 = busca_vertice(g, v2);
    TVizinho *resp = NULL;
    //checa se ambos os vértices existem
    if((pv1 != NULL) && (pv2 != NULL)){
        //percorre a lista de vizinhos de v1 procurando por vizinho v2
        resp = pv1->prim_vizinho;
        while((resp != NULL) && (resp->id_vizinho != v2)){
            resp = resp->prox;
        }
    }
    return resp;
}

//Inserção de vértice
TGrafo *insere_vertice(TGrafo *g, int x){
    TGrafo *p = busca_vertice(g, x);
    if(p == NULL){
        p = (TGrafo*) malloc(sizeof(TGrafo));
        p->id_vertice = x;
        p->prox = g;
        p->prim_vizinho = NULL;
        g = p;
    }
    return g;
}

//Inserção de aresta em grafo não orientado
void insere_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = busca_vertice(g, v1);
    TVizinho *nova = (TVizinho *) malloc(sizeof(TVizinho));
    nova->id_vizinho = v2;
    nova->prox = p->prim_vizinho;
    p->prim_vizinho = nova;
}

void insere_aresta(TGrafo *g, int v1, int v2){
    TVizinho *v = busca_aresta(g, v1, v2);
    if(v == NULL){
        insere_um_sentido(g, v1, v2);
        insere_um_sentido(g, v2, v1);
    }
}

//inserção de aresta em digrafo 
void insere_aresta_digrafo(TGrafo *g, int v1, int v2){
    TVizinho *v = busca_aresta(g, v1, v2);
    if(v == NULL){
        insere_um_sentido(g, v1, v2);
    }
}

//Exclusão de aresta em grafo não orientado
void retira_um_sentido(TGrafo *g, int v1, int v2){
    TGrafo *p = busca_vertice(g, v1);
    if(p != NULL){
        TVizinho *ant = NULL;
        TVizinho * atual = p->prim_vizinho;
        while ((atual) && (atual ->id_vizinho != v2)) {
            ant = atual;
            atual = atual->prox;
        }
        if(ant == NULL){
            p->prim_vizinho = atual->prox;
        } else {
            ant->prox = atual->prox;
        }
        free(atual);
    }
}

// Exclusão de aresta em grafo não orientado(cont.)
void retira_aresta(TGrafo *g, int v1, int v2){
    TVizinho* v = busca_aresta(g, v1, v2);
    if(v != NULL){
        retira_um_sentido(g, v1, v2);
        retira_um_sentido(g, v2, v1);
    }
}

//exclusão de aresta em digrafo 
void retira_aresta_digrafo(TGrafo *g, int v1, int v2){
    TVizinho* v = busca_aresta(g, v1, v2);
    if(v != NULL){
        retira_um_sentido(g, v1, v2);
    }
}

//impressão do grafo 
void imprime_recursivo(TGrafo *g){
    if(g != NULL){
        printf("Vértice: %d:\n", g->id_vertice);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;
        while(v){
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");
        imprime_recursivo(g->prox);
    }
}

//liberação da estrutura (implementação recursiva)
void libera_recursivo(TGrafo *g){
    if(g != NULL){
        libera_vizinho_recursivo(g->prim_vizinho);
        libera_recursivo(g->prox);
        free(g);
    }
}

void libera_vizinho_recursivo(TVizinho *v){
    if(v != NULL){
        libera_vizinho_recursivo(v->prox);
        free(v);
    }
}


void main(){
    
    printf("Grafo USP");
    
    
    
    return 0;
}