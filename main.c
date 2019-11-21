//Daniel De Marco Fucci

#include <sudoku.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char hexAlf[17] = "0123456789ABCDEF";
    MATRIX_ELEM **matrix=createMatrix();
    checkPossible(matrix, hexAlf);
    findUniqueSolution(matrix, hexAlf);
    solve(matrix);
    printMatrix(matrix);
    free(matrix);
    return 0;
}