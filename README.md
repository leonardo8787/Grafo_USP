<h1>Grafo e Dígrafos USP</h1>

<h4>Grafos</h4>
Grafos são estruturas de dados formadas por um conjunto de vértices e um conjunto de arestas.

<p>
	<img src="https://www.revista-programar.info/wp-content/uploads/2007/09/grafo-exemplo-2.gif" width="300" height="200">
</p>

<h4>Aplicações</h4> 
Associando-se significados aos vértices e às arestas, o grafo passa a constituir um modelo de uma situação ou informação real.

<h4>Grade Curricular</h4>

<p>
	<img src="https://www.matteus.dev/wp-content/uploads/matriz-13.jpg" width="300" height="200">
</p>

<h4>Rotas de voos</h4>

<p>
	<img src="https://www.aviacaocomercial.net/rotastam.2011intl.jpg" width="300" height="200">
</p>

<h4>Redes Socias</h4>

<p>
	<img src="https://www.ibpad.com.br/wp-content/uploads/2021/07/rede-de-co-ocorr%C3%AAncia-de-coment%C3%A1rios-em-not%C3%ADcias.png" width="300" height="200">
</p>

<h4>Definição Formal</h4>

Um grafo G é representado por um conjunto (não vazio) V de vértices e um conjunto (possivelmente vazio) E de arestas (edges).

G = (V, E)<br>
|V| é a quantidade de vértices de G<br>
|E| é a quantidade de arestas de G<br>

<h4>Grafos orientados x não orientados</h4>

As arestas podem ter uma direção ou podem ser bi-direcionais. Grafos orientados: as arestas possuem uma direção, também são chamados de grafos dirigidos ou digrafos. Grafos não orientados: as arestas são bi-dimencionais (se existe uma conexão a -> b então também existe uma conexão b -> a).

<h4>Definições e Terminologia</h4>

Um grafo é valorado se possuir valores (pesos) associados às arestas e/ou aos vértices. Exemplo: num grafo de rotas de voo uma aresta pode ser valorada com a distância entre os dois aeroportos que ela conecta.

<h2>Implementação</h2>

Veremos a implementação de grafos usando lista de adjacência! São flexíveis para acomodar inserções e remoções, ao contrário das matrizes de adjacência e incidência. Facilitam a identificação dos vértices dos vértices do grafo, ao contrário das listas de incidência.

~~~
typedef struct vizinho {
    int id_vizinho;
    struct vizinho *prox;
}TVizinho;

typedef struct grafo {
    int id_vertice;
    TVizinho *prim_vizinho;
    struct grafo *prox;
}TGrafo;
~~~

inicialisação da estrutura:

~~~
TGrafo *inicializa() {
    return NULL;
}
~~~

impressão do grafo: 

~~~
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
~~~

Liberação da estrutura: 

~~~
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
~~~

Busca por vértice x:

~~~
TGrafo* busca_vertice(TGrafo* g, int x){
    while((g != NULL) && (g->id_vertice != x)){
        g = g->prox;
    }
    return g;
}
~~~

Busca por aresta (v1, v2) ou {v1, v2}

~~~
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
~~~

Inserção de vértice:

~~~
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
~~~

Inserção de aresta em grafo não orientado:

~~~
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
~~~

Inserção de aresta em digrafo:

~~~
void insere_aresta_digrafo(TGrafo *g, int v1, int v2){
    TVizinho *v = busca_aresta(g, v1, v2);
    if(v == NULL){
        insere_um_sentido(g, v1, v2);
    }
}
~~~

Esclusão de aresta em grafo não orientado:

~~~
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
~~~

Esclusão de aresta em grafo não orientado(cont.):

~~~
void retira_aresta(TGrafo *g, int v1, int v2){
    TVizinho* v = busca_aresta(g, v1, v2);
    if(v != NULL){
        retira_um_sentido(g, v1, v2);
        retira_um_sentido(g, v2, v1);
    }
}
~~~

Esclusão de aresta em digrafo: 

~~~
void retira_aresta_digrafo(TGrafo *g, int v1, int v2){
    TVizinho* v = busca_aresta(g, v1, v2);
    if(v != NULL){
        retira_um_sentido(g, v1, v2);
    }
}
~~~

Impressão do grafo (implementação recursiva): 

~~~
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
~~~

Liberação da estrutura (implementação recursiva): 

~~~
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
~~~
