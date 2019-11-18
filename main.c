//Daniel De Marco Fucci
//BSI 2019
//11218639

#include <sudoku.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    MATRIX_ELEM **matrix=createMatrix();
    solve(matrix);
    printMatrix(matrix);
    return 0;
}