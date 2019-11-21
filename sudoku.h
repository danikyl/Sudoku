//Daniel De Marco Fucci

#ifndef _SUDOKU_
#define _SUDOKU_

#define NSIZE 16

typedef struct matrix_elem {
    char symbol;
    char *possibleValues;
    int nPossible;
} MATRIX_ELEM;

void checkPossible(MATRIX_ELEM **matrix, char *alfaHex);

void printMatrix(MATRIX_ELEM **matrix);

MATRIX_ELEM **createMatrix();

int solve(MATRIX_ELEM **matrix);

void findUniqueSolution(MATRIX_ELEM **matrix, char *alfaHex);

void freeMatrix(MATRIX_ELEM **matrix);


#endif