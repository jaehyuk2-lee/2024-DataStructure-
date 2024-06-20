#include <stdio.h>
#include "matrix.h"

int main() {
    int a[ROW][COL] = {{1,0,0},{1,0,0},{1,0,0}};
    int b[ROW][COL] = {{1,1,1},{0,0,0},{0,0,0}};
    int c[ROW][COL] = {{0,0,0},{0,0,0},{0,0,0}};

    matrix_print(a);
    printf("\n");
    matrix_print(b);
    printf("\n");

    matrix_add(a,b,c);
    matrix_print(c);
    printf("\n");

    matrix_init(c);
    matrix_mult(a,b,c);
    matrix_print(c);
    printf("\n");

    matrix_init(c);
    matrix_trans(a, c);
    matrix_print(c);
    printf("\n");

    return 0;
}

void matrix_init(int a[ROW][COL]) {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            a[i][j] = 0;
        }
    }
}
void matrix_add(int a[ROW][COL], int b[ROW][COL], int c[ROW][COL]) {
    printf("a + b = \n");
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    } 
}
void matrix_mult(int a[ROW][COL], int b[ROW][COL], int c[ROW][COL]) {
    printf("a * b = \n");
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            for(int k = 0; k < ROW; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }     
}
void matrix_trans(int a[ROW][COL], int b[ROW][COL]) {
    printf("a transpose = \n");
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            b[j][i] = a[i][j];
        }
    }
}
void matrix_print(int a[ROW][COL]) {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    } 
}