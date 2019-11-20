//Daniel De Marco Fucci
//BSI 2019
//11218639

#include <sudoku.h>
#include <stdlib.h>
#include <stdio.h>

void printMatrix(MATRIX_ELEM **matrix) {
    int i, j;
    for (i=0; i<NSIZE; i++) {
        for (j=0; j<NSIZE-1; j++) {
            printf ("%c ", matrix[i][j].symbol);
        }
        printf ("%c", matrix[i][NSIZE-1].symbol);
        if (i<NSIZE-1)printf("\n");
    }
}

MATRIX_ELEM **createMatrix() {
    int i, j;
    MATRIX_ELEM **matrix = (MATRIX_ELEM **) malloc (sizeof(MATRIX_ELEM *) * NSIZE+1);
    for (i=0; i<NSIZE; i++) {
        matrix[i]=(MATRIX_ELEM *) calloc (NSIZE+1, sizeof(MATRIX_ELEM));
    }
    for (i=0; i<NSIZE; i++) {
        for (j=0; (matrix[i][j].symbol = getchar()) != '\n' && j<NSIZE; j++); 
    }
    return matrix;

}

int isBlankSpace (int line, int col, MATRIX_ELEM **matrix) {
    if (matrix[line][col].symbol == '.') return 1;
    else return 0;
}

int posValidator(char symbol, int line, int col, MATRIX_ELEM **matrix) {
    int i, j, quadrantLine, quadrantColumn;
    //validating column
    for (i=0; i<NSIZE; i++) {
        if (matrix[i][col].symbol == symbol) return 0;
    }
    //validating line
    for (i=0; i<NSIZE; i++) {
        if (matrix[line][i].symbol == symbol) return 0;
    }
    //validating quadrant
    quadrantLine=line - line % 3;
    quadrantColumn= col - col % 3;
    for (i=quadrantLine; i<quadrantLine+3; i++) {
        for (j=quadrantColumn; j< quadrantColumn+3; j++) {
            if (matrix[i][j].symbol == symbol) return 0;
        }
    }
    return 1;
}

//Test possibilities of insertion
int findEmpty(int *line, int *col, MATRIX_ELEM **matrix) {
    *line=0;
    *col=0;
    while (*line < NSIZE) {
        *col=0;
        while (*col < NSIZE) {
            if (isBlankSpace(*line, *col, matrix)) {
                return 1;
            }
            *col += 1;
        }
        *line += 1;
    }
    return 0;
}





int solve(MATRIX_ELEM **matrix, char *hexAlf) {
    int auxChar;
    int line=0, col=0;
    if (!findEmpty(&line, &col, matrix)) return 1;
    for (auxChar=0; auxChar<NSIZE; auxChar++) {
        if (posValidator(hexAlf[auxChar], line, col, matrix)) {
            matrix[line][col].symbol = hexAlf[auxChar];
            if (solve(matrix, hexAlf)) return 1;
            else matrix[line][col].symbol ='.';
        }
        
    }
    return 0;
}

