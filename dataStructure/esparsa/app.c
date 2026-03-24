#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0

typedef struct tempNo {
    float value;
    int colunm;
    struct tempNo* next;
} NO;

typedef NO* PONT;

typedef int boolean;

typedef struct 
{
    PONT* A;
    int lines;
    int colunms;
} MATRIX;

void initializerMatrix(MATRIX* m, int lin, int col) {
    int i;
    m->lines = lin;
    m->colunms = col;
    m->A = (PONT*) malloc(lin*sizeof(PONT));
    for(i=0; i<lin; i++) m->A[i] = NULL;
}

boolean atribuiteMatrix(MATRIX* m, int lin, int col, float val) {
    if(lin < 0 || lin >= m->lines ||
    col < 0 || col >= m->colunms) return false;
    PONT before = NULL;
    PONT current = m->A[lin];
    while(current != NULL && current->colunm < col) {
        before = current;
        current = current->next;
    }
    if(current != NULL && current->colunm == col) {
        if(val == 0) {
            if(before == NULL) m->A[lin] = current->next;
            else before->next = current->next;
            free(current);
        }
        else current->value = val;
    }
    else {
        PONT new = (PONT) malloc(sizeof(NO));
        new->colunm = col;
        new->value = val;
        new->next = current;
        if(before == NULL) m->A[lin] = new;
        else before->next = new;
    }
}

float valueMatrix(MATRIX* m, int lin, int col) {
    if(lin < 0 || lin >= m->lines ||
    col < 0 || col >= m->colunms) return 0;

    PONT current = m->A[lin];
    while(current != NULL && current->colunm < col) {
        current = current->next;
    }
    if(current != NULL && current->colunm == col) {
        return current->value;
    }
    return 0;
}

void printMatrix(MATRIX* m, int lin, int col) {
    int l; int c;
    for(l=0; l < lin; l++) {
        for(c=0; c < col; c++) {
            float current = valueMatrix(m, l, c);
            if(current != 0) {
               printf("%.2f   ", current);
            }
            else printf("0.00   ");
        }
        printf("\n");
    }
}

int main() {
    MATRIX* m1 = (MATRIX*) malloc(sizeof(MATRIX));
    int lin = 3;
    int col = 4;
    initializerMatrix(m1, lin, col);

    atribuiteMatrix(m1, 0, 0, 5.0);

    printMatrix(m1, lin, col);

    return 0;
}