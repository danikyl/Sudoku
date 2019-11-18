//Daniel De Marco Fucci
//BSI 2019
//11218639

#ifndef _SUDOKU_
#define _SUDOKU_

#define lineN 16
#define colN 16

typedef struct matrix_elem {
    char symbol;
    int isSpot;
} MATRIX_ELEM;

void printMatrix(MATRIX_ELEM **matrix);

MATRIX_ELEM **createMatrix();

void solve(MATRIX_ELEM **matrix);



#endif