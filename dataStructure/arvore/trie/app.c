#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define N_ALPHABET 26

typedef int boolean;

typedef boolean TYPERET;

typedef struct node {
    struct node *childrens[N_ALPHABET];
    TYPERET end;
} NODE;

typedef NODE* PONT;

PONT createNode() {
    PONT p = NULL;
    p = (PONT)malloc(sizeof(NODE));

    if(p) {
        p->end = false;
        int i;
        for(i=0; i<N_ALPHABET; i++) {
            p->childrens[i] = NULL;
        }
    }
}

PONT initialize() {
    return(CreateNode());
}

int mapIndex(char c) {
    return((int)c - (int)'a');
}

void insert(PONT root, char *key) {
    int level;
    int size = strlen(key);
    int i;

    PONT p = root;
    for(level=0; level<size; level++) {
        i = mapIndex(key[level]);
        if(!p->childrens[i]) {
            p->childrens[i] = createNode();
        }
        p = p->childrens[i];
    }
    p->end = true;
}

boolean search(PONT root, char *key) {
    int level;
    int size = strlen(key);
    int i;
    PONT p = root;

    for(level=0; level<size; level++) {
        i = mapIndex(key[level]);
        if(!p->childrens[i]) return(false);
    }
    return(p->end);
}

int main() {
    PONT r = initialize();

    return 0;
}