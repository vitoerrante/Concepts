#include <stdio.h>
#include <malloc.h>
#define MAX 50
#define INVALID -1

typedef int TYPEKEY;

typedef struct 
{
    TYPEKEY key;
} REGISTER;

typedef struct
{
    REGISTER reg;
    int next;
} ELEMENT;

typedef struct
{
    ELEMENT A[MAX];
    int start;
    int available;
} LIST;

void initializeList(LIST* l) {
    int i;
    for(i=0; i<MAX-1; i++) {
        l->A[i].next = i + 1;
    }
    l->A[MAX-1].next=INVALID;
    l->start=INVALID;
    l->available=0;
}

int size(LIST* l){
    int i = l->start;
    int siz = 0;
    while(i != INVALID) {
        siz++;
        i = l->A[i].next;
    }
    return siz;
}

int searchSequencial(LIST* l, TYPEKEY key) {
    int i = l->start;
    while(i != INVALID && l->A[i].reg.key < key){
        i = l->A[i].next;
    }
    if(i != INVALID && l->A[i].reg.key == key){
        return i;
    }
    else return INVALID;
}

int getAvailable(LIST* l) {
    int result = l->available;
    if(l->available != INVALID) {
        l->available = l->A[l->available].next;
    }
    return result;
}

bool insertElemListOrd(LIST* l, REGISTER reg) {
    if(l->available == INVALID) return false;
    int before = INVALID;
    int i = l->start;
    TYPEKEY key = reg.key;
    while((i != INVALID) && (l->A[i].reg.key < key)) {
        before = i;
        i = l->A[i].next;
    }
    if(i!=INVALID && l->A[i].reg.key == key) return false;
    i = getAvailable(l);
    l->A[i].reg = reg;
    if(before == INVALID) {
        l->A[i].next = l->start;
        l->start = i;
    } else {
        l->A[i].next = l->A[before].next;
        l->A[before].next = i;
    }
    return true;
}

void printList(LIST* l) {
    int i = l->start;
    printf("LIST: \n");
    while(i != INVALID) {
        printf("%i\n", l->A[i].reg.key);
        i = l->A[i].next;
    }
    printf("\n");
}

int main() {
    LIST* l1 = (LIST*) malloc(sizeof(LIST));
    initializeList(l1);

    REGISTER r;

    int values[] = {30, 10, 50, 20, 40};
    int n = 5;

    for(int i = 0; i < n; i++) {
        r.key = values[i];
        insertElemListOrd(l1, r);
    }

    printList(l1);

    return 0;
}