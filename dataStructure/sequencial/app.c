#include <stdio.h>
#include <malloc.h>

#define MAX 50

typedef int TYPEKEY;

typedef struct 
{
    TYPEKEY key;
} REGISTER;

typedef struct 
{
    REGISTER A[MAX+1];
    int nroElem;
} LIST;

void initializeList(LIST* l) {
    l->nroElem = 0;
    l->A[0].key = 10;
    l->A[1].key = 21;
    l->A[2].key = 55;
    l->nroElem = 3;
}

bool insertList(LIST* l, REGISTER reg, int i){
    int j;
    if(l->nroElem == MAX || (i < 0) || (i > l->nroElem)){
        return false;
    }
    for(j = l->nroElem; j > i; j--) {
        l->A[j] = l->A[j-1];
    }
    l->A[i] = reg;
    l->nroElem++;
    return true;
}

bool insertElemListOrd(LIST* l, REGISTER reg) {
    if(l->nroElem == MAX) return false;
    int pos = l->nroElem;
    while (pos > 0 && l->A[pos-1].key > reg.key)
    {
        l->A[pos] = l->A[pos-1];
        pos--;
    }
    l->A[pos] = reg;
    l->nroElem++;
    
}

void printList(LIST* l) {
    int i;
    printf("List:\n");
    for(i = 0; i < l->nroElem; i++){
        printf("%i\n", l->A[i].key);
    }
}

int searchSequencial(LIST* l, TYPEKEY ch) {
    int i = 0;
    while (i < l->nroElem) {
        printf("%i\n", i);
        if(ch == l->A[i].key) {
            return i;
        }
        else i++;
    }
    return -1;
}

int searchSentinel(LIST* l, TYPEKEY ch) {
    int i = 0;
    l->A[l->nroElem].key = ch;
    while (l->A[i].key != ch) i++;
    if(i == l->nroElem) return -1;
    else return i; 
}

int searchBinary(LIST* l, TYPEKEY ch) {
    int left, right, center;
    left = 0;
    right = l->nroElem-1;
    while(left <= right) {
        center = (left + right) / 2;
        if(l->A[center].key == ch) return center;
        else {
            if(l->A[center].key < ch) left = center + 1;
            else right = center - 1;
        }
    }
    return -1;
}

bool deleteElemList(TYPEKEY ch, LIST* l) {
    int pos, j;
    pos = searchSequencial(l, ch);
    if(pos == -1) {
        return false;
    }
    for(j = pos; j < l->nroElem-1; j++) {
        l->A[j] = l->A[j+1];
    }
    l->nroElem--;
    return true;
}

int main() {
    LIST* l1 = (LIST*) malloc(sizeof(LIST));

    initializeList(l1);

    // REGISTER reg;

    // reg.key = 21;

    // insertList(l1, reg, 0);

    // deleteElemList(10, l1);

    REGISTER reg;

    reg.key = 15;

    insertElemListOrd(l1, reg);

    printList(l1);

    if(searchBinary(l1, 255) != -1) printf("Search Binary OK \n");

    return 0;
}