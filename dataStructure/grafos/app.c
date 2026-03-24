#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int boolean;
typedef int TYPEWEIGHT;

typedef struct adjacency
{
    int vertice;
    TYPEWEIGHT weight;
    struct adjacency *prox;   
} ADJACENCY;


typedef struct vertice {
    ADJACENCY *head;
} VERTICE;

typedef struct graph {
    int vertices;
    int edges;
    VERTICE *adj;
} GRAPH;

GRAPH *createGraph(int v){
    GRAPH *g = (GRAPH *)malloc(sizeof(GRAPH));
    g->vertices = v;
    g->edges = 0;
    g->adj = (VERTICE *)malloc(v*sizeof(VERTICE));
    int i;
    for(i=0; i<v; i++) {
        g->adj[i].cab = NULL;
    }
    return(g);
}

ADJACENCY *createAdj(int v, int weight) {
    ADJACENCY *temp = (ADJACENCY *)malloc(sizeof(ADJACENCY));
    temp->vertice = v;
    temp->weight = weight;
    temp->prox = NULL;
    return(temp);
}

bool createEdge(GRAPH *gr, int vi, int vf, TYPEWEIGHT p) {
    if(!gr) return(false);
    if((vf<0) || (vf >= gr->vertices)) {
        return(false);
    }
    if((vi<0) || (vi >= gr->vertices)) {
        return(false);
    }
    ADJACENCY *new = createAdj(vf, p);
    new->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = new;
    gr->edges++;
    return(true);
}

void print(GRAPH *gr) {
    printf("Vertices; %d. Edges: &d.\n", gr->vertices, gr->edges);
    int i;
    for(i=0; i<gr->vertices; i++) {
        print("v%d", i);
        ADJACENCY *ad = gr->adj[i].cab;
        while(ad) {
            printf("v%d(%d)", ad->vertice, ad->weight);
            ad = ad->prox;
        }
        printf("\n");
    }
}

int main() {
    return 0;
}