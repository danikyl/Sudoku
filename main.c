//Daniel De Marco Fucci
//BSI 2019
//11218639

#include <sudoku.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char hexAlf[17] = "0123456789ABCDEF";
    MATRIX_ELEM **matrix=createMatrix();
    solve(matrix, hexAlf);
    printMatrix(matrix);
    return 0;
}