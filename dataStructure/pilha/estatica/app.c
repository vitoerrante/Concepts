#include <stdio.h>
#include <malloc.h>
#define MAX 50

#define true 1
#define false 0

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef int boolean;

typedef int TYPEKEY;

typedef struct
{
    TYPEKEY key;
} REGISTER;

typedef struct {
    REGISTER A[MAX];
    int top;
} STACK;

void initializer(STACK* p) {
    p->top = -1;
}

int size(STACK* p) {
    return p->top + 1;
}

void printStack(STACK* p) {
    printf("Stack: \n");
    int i;
    for (i=p->top; i > 0; i--) {
        printf("%i\n", p->A[i].key);
    }
    printf("\n");
}

bool insertElemStack(STACK* p, REGISTER reg) {
    if (p->top >= MAX-1) return false;
    p->top = p->top+1;
    p->A[p->top] = reg;
    return true;
}

void insertMultipleElemStack(STACK* p, int* values, int size) {
    REGISTER reg;
    int i;
    for (i = 0; i < size; i++) {
        reg.key = values[i];
        insertElemStack(p, reg);
    }
}

bool deleteStack(STACK* p, REGISTER* reg) {
    if(p->top == -1) return false;
    *reg = p->A[p->top];
    p->top = p->top-1;
    return true;
}

int main () {
    STACK* p1 = (STACK*) malloc(sizeof(STACK));

    int values[] = { 5, 10, 15, 20, 25 };
    int size = ARRAY_SIZE(values);

    insertMultipleElemStack(p1, values, size);

    printStack(p1);

    return 0;
}