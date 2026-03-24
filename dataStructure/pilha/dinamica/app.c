#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef  int TYPEKEY;

typedef struct {
    TYPEKEY key;
} REGISTER;

typedef struct aux {
    REGISTER reg;
    struct aux* prox;
} ELEMENT;

typedef ELEMENT* PONT;

typedef struct {
    PONT top;
} STACK;

void initialize(STACK* p) {
    p->top = NULL;
}

void reset(STACK* p) {
    PONT delete;
    PONT position = p->top;
    while(position != NULL) {
        delete = position;
        position = position->prox;
        free(delete);
    }
    p->top = NULL;
}

int stackSize(STACK* p) {
    PONT end = p->top;
    int size = 0;
    while(end != NULL) {
        size++;
        end = end->prox;
    }
    return size;
}

bool checkEmpty(STACK* p) {
    if(p->top == NULL) return true;
    return false;
}

void printStack(STACK* p) {
    PONT end = p->top;
    printf("STACK:\n");
    while(end != NULL) {
        printf("%i\n", end->reg.key);
        end = end->prox;
    }
    printf("\n");
}

bool pushStack(STACK*p, REGISTER reg) {
    PONT new = (PONT) malloc(sizeof(ELEMENT));
    new->reg = reg;
    new->prox = p->top;
    p->top = new;
    return true;
}

bool popStack(STACK*p, REGISTER* reg) {
    if(p->top == NULL) return false;
    *reg = p->top->reg;
    PONT delete = p->top;
    p->top = p->top->prox;
    free(delete);
    return true;
}

bool pushMultiplesStack(STACK* p, int* values, int arraySize) {
    REGISTER reg;
    int i;
    for(i = 0; i < arraySize; i++) {
        reg.key = values[i];
        pushStack(p, reg);
    }
    return true;
}

int main() {
    STACK* p1 = (STACK*) malloc(sizeof(STACK));

    initialize(p1);

    int values[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    pushMultiplesStack(p1, values, ARRAY_SIZE(values));

    REGISTER* reg = malloc(sizeof(REGISTER));

    popStack(p1, reg);

    printStack(p1);

    return 0;
}