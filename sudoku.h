//Daniel De Marco Fucci
//BSI 2019
//11218639

#ifndef _SUDOKU_
#define _SUDOKU_

#define NSIZE 9

typedef struct matrix_elem {
    char symbol;
} MATRIX_ELEM;

void printMatrix(MATRIX_ELEM **matrix);

MATRIX_ELEM **createMatrix();

int solve(MATRIX_ELEM **matrix, char *hexAlf);



#endif