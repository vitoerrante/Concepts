#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int boolean;
typedef int TYPEKEY;

typedef struct node {
    TYPEKEY key;
    struct node *firstChildren;
    struct node *nextChildren;
} NODE;

typedef NODE* PONT;

PONT createNewNode(TYPEKEY key) {
    PONT new = (PONT)malloc(sizeof(NODE));
    new->firstChildren = NULL;
    new->nextChildren = NULL;
    new->key = key;
}

PONT initialize(TYPEKEY key) {
    return(createNewNode(key));
}

boolean insert(PONT root, TYPEKEY newKey, TYPEKEY keyParent) {
    PONT parent = searchKey(keyParent, root);
    if(!parent) return false;
    PONT children = createNewNode(newKey);
    PONT p = parent->firstChildren;
    if(!p) parent->firstChildren = children;
    else {
        while(p->nextChildren) {
            p = p->nextChildren;
        }
        p->nextChildren = children;
    }
    return true;
}

PONT searchKey(TYPEKEY key, PONT root) {
    if(root == NULL) return NULL;
    if(root->key == key) return root;
    PONT p = root->firstChildren;
    while(p) {
        PONT resp = searchKey(key, p);
        if(resp) return (resp);
        p = p->nextChildren;
    }
    return NULL;
}

void printTree(PONT root) {
    if(root == NULL) return;
    printf("%d(", root->key);
    PONT p = root->firstChildren;
    while(p) {
        printTree(p);
        p = p->nextChildren;
    }
    printf(")");
}

int main() {
    PONT r = initialize(8);
}