#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int boolean;
typedef int TYPEKEY;
typedef struct aux {
    TYPEKEY key;
    struct aux *left, *right;
} NODE;
typedef NODE* PONT;

PONT initialize() {
    return(NULL);
}

PONT add(PONT root, PONT node) {
    if (root == NULL) return(node);

    if(node->key < root->key) {
        root->left = add(root->left, node);
    }
    else {
        root->right = add(root->right, node);
    }
    return(root);
}

PONT createNewNode(TYPEKEY key) {
    PONT newNode = (PONT)malloc(sizeof(NODE));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = key;
    return(newNode);
}

PONT search(TYPEKEY key, PONT root) {
    if(root == NULL) return(NULL);
    if(root->key == key) return (root);
    if(root->key > key) {
        return(search(key, root->left));
    }
    return(search(key, root->right));
}

PONT searchNode(PONT root, TYPEKEY key, PONT *parent) {
    PONT current = root;
    *parent = NULL;
    while(current) {
        if(current->key == key) return(current);
        *parent = current;
        if(key < current->key) current = current->left;
        else current = current->right;
    }
    return(NULL);
}

PONT removeNode(PONT root, TYPEKEY key) {
    PONT parent, node, p, q;
    node = searchNode(root, key, &parent);
    if(node == NULL) return(root);
    if(!node->left || !node->right){
        if(!node->left) q = node->right;
        else q = node->left;
    }
    else {
        p = node;
        q = node->left;
        while(q->right) {
            p = q;
            q = q->right;
        }
        if(p != node) {
            p->right = q->left;
            q->left = node->left;
        }
        q->right = node->right;
    }
    if(!parent) {
        free(node);
        return(q);
    }
    if(key < parent->key) parent->left = q;
    else parent->right = q;
    free(node);
    return(root);
}

void printTree(PONT root) {
    if(root != NULL) {
        printf("%i", root->key);
        printf("( ");
        printTree(root->left);
        printTree(root->right);
        printf(" )");
    }
}

int numberNodes(PONT root) {
    if(!root) return 0;
    return(numberNodes(root->left) + 1 + numberNodes(root->right));
}

int main() {
    PONT r = initialize();
    int values[7] = {15, 8, 2, 12, 23, 20, 30};

    int i;
    for(i=0; i < sizeof(values) / sizeof(values[0]); i++) {
        PONT node = createNewNode(values[i]);
        r = add(r, node);
    }

    printTree(r);

    printf("Number of Nodes: %d\n", numberNodes(r));

    return 0;
}