#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int boolean;
typedef int TYPEKEY;

typedef struct aux
{
    TYPEKEY key;
    struct aux *left;
    struct aux *right;
    int h;
} NODE, *PONT;

PONT createNewNode(TYPEKEY key) {
    PONT newNode = (PONT)malloc(sizeof(NODE));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = key;
    newNode->h = 0;
    return(newNode);
}

PONT initialize() {
    return(NULL);
}

int max(int a, int b) {
    if(a > b) return a;
    return b;
}

int height(PONT root) {
    if(!root) return(-1);
    return(root->h);
}

PONT right(PONT r) {
    PONT aux;
    aux = r->left;
    r->left = aux->right;
    aux->right = r;

    r->h = max(height(r->right), height(r->left)) +1;
    aux->h = max(height(aux->left), r->h) +1;

    return(aux);
}

PONT left(PONT r) {
    PONT aux;
    aux = r->right;
    r->right = aux->left;
    aux->left = r;

    r->h = max(height(r->right), height(r->left)) +1;
    aux->h = max(height(aux->left), r->h) +1;

    return(aux);
}

PONT leftRight(PONT r) {
    r->left = left(r->left);
    return(right(r));
}

PONT rightLeft(PONT r){
    r->left = right(r->right);
    return(left(r));
}

PONT insert(PONT root, TYPEKEY key) {
    if(!root) return(createNewNode(key));
    if(key < root->key) {
        root->left = insert(root->left, key);
        if((height(root->left) - height(root->right)) == 2) {
           if(key < root->left->key) {
            root = right(root);
           } 
           else {
            root = leftRight(root);
           }
        }
    }
    else {
        if(key > root->key) {
            root->right = insert(root->right, key);
            if((height(root->right) - height(root->left)) == 2) {
                if(key > root->right->key) {
                    root = left(root);
                }
                else {
                    root = rightLeft(root);
                }
            }
        }
    }
    root->h = max(height(root->left), height(root->right) + 1);
    return (root);
}

int main() {
    PONT r = initialize();
}