#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define true 1
#define false 0

typedef struct tempNo {
    float value;
    int colunm;
    struct tempNo* next;
} NO;

typedef NO* PONT;

typedef int boolean;

typedef struct {
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
    return true;
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

void insertMultipleValue(MATRIX* m, int lin, int col, float* values) {
    int i=0, l, c;
    for(l=0; l < lin; l++) {
        for(c=0; c < col; c++) {
            atribuiteMatrix(m, l, c, values[i]);
            i++;
        }
    }
}

void matricesMultiplySameProportion (int lin, int col, MATRIX* m1, MATRIX* m2, MATRIX* result) {
    int l, c, c2;
    float current, sum;
    for(l=0; l < lin; l++) {
        // lin m1
        for(c=0; c < col; c++) {
            // col m1
            sum = 0;
            for(c2=0; c2 < col; c2++){
                // col m2
                float m1_current = valueMatrix(m1, l, c2);
                float m2_current = valueMatrix(m2, c2, c);

                float current = m1_current * m2_current;

                sum = sum + current;
            }
            atribuiteMatrix(result, l, c, sum);
        }
    }
}


int main() {
    MATRIX* m1 = (MATRIX*) malloc(sizeof(MATRIX));
    MATRIX* m2 = (MATRIX*) malloc(sizeof(MATRIX));
    MATRIX* matrixResult = (MATRIX*) malloc(sizeof(MATRIX));
    int lin, col;
    lin = 3;
    col = 3;

    initializerMatrix(m1, lin, col);
    initializerMatrix(m2, lin, col);
    initializerMatrix(matrixResult, lin, col);

    float values[9] = {
        5.0, 3.0, 2.0,
        1.0, 2.0, 3.0,
        8.0, 1.0, 6.0
    };
    float values2[9] = {
        1.0, 2.0, 3.0,
        3.0, 1.0, 2.0,
        3.0, 2.0, 1.0
    };

    insertMultipleValue(m1, lin, col, values);
    insertMultipleValue(m2, lin, col, values2);

    matricesMultiplySameProportion(lin, col, m1, m2, matrixResult);

    printMatrix(matrixResult, lin, col);

    return 0;
}