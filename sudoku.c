//Daniel De Marco Fucci
//BSI 2019
//11218639

#include <sudoku.h>
#include <stdlib.h>
#include <stdio.h>

void printMatrix(MATRIX_ELEM **matrix) {
    int i, j;
    for (i=0; i<lineN; i++) {
        for (j=0; j<colN-1; j++) {
            printf ("%c ", matrix[i][j].symbol);
        }
        printf ("%c", matrix[i][colN-1].symbol);
        if (i<lineN-1)printf("\n");
    }
}

MATRIX_ELEM **createMatrix() {
    int i, j;
    MATRIX_ELEM **matrix = (MATRIX_ELEM **) malloc (sizeof(MATRIX_ELEM *) * lineN+1);
    for (i=0; i<lineN; i++) {
        matrix[i]=(MATRIX_ELEM *) calloc (colN+1, sizeof(MATRIX_ELEM));
    }
    for (i=0; i<lineN; i++) {
        for (j=0; (matrix[i][j].symbol = getchar()) != '\n' && j<colN; j++) {
            if (matrix[i][j].symbol == '.') matrix[i][j].isSpot = 1;
        }
    }
    return matrix;

}
int posValidator(char symbol, int line, int col, MATRIX_ELEM **matrix) {
    int i, j, quadrantLine, quadrantColumn;
    //validating column
    for (i=0; i<lineN; i++) {
        if (matrix[i][col].symbol == symbol) return 0;
    }
    //validating line
    for (i=0; i<colN; i++) {
        if (matrix[line][i].symbol == symbol) return 0;
    }
    //validating quadrant
    quadrantLine=line - line % 4;
    quadrantColumn= col - col % 4;
    for (i=quadrantLine; i<quadrantLine+4; i++) {
        for (j=quadrantColumn; j< quadrantColumn+4; j++) {
            if (matrix[i][j].symbol == symbol) return 0;
        }
    }
    return 1;
}

int isBlankSpace (int line, int col, MATRIX_ELEM **matrix) {
    if (matrix[line][col].symbol == '.') return 1;
    else return 0;
}

int isSpot (int line, int col, MATRIX_ELEM **matrix) {
    if (matrix[line][col].isSpot) return 1;
    else return 0;
}
//Test possibilities of insertion
int letterInsert(int line, int col, MATRIX_ELEM **matrix) {
    char hexAlf[17] = "0123456789ABCDEF";
    int i, j, starPoint;
    if (isSpot(line, col, matrix)) {
        if (isBlankSpace(line, col, matrix)) starPoint=0; 
        else {
            for (i=0;i<16; i++) {
                if (matrix[line][col].symbol == hexAlf[i]) {
                    starPoint=i;
                    break;
                }
            }
        }
        for (i=starPoint; i<16; i++) {
            if (posValidator(hexAlf[i], line, col, matrix)) {
                matrix[line][col].symbol = hexAlf[i];
                return 1;
            }
        }
    }
    
    return 0;
}





void solve(MATRIX_ELEM **matrix) {
    int i, j, k, l;
    //going through matrix
    for (i=0; i<lineN; i++) {
        for (j=0; j<colN; j++) {
            //checking is is a blank spot
            if (isBlankSpace(i, j, matrix)) {
                k=i;
                l=j;
                //Testing letters from hex alphabet to insert in this matrix position
                //When it fails to find valid letter for current position, uses backtrack to change previous positions
                while (!letterInsert(i, j, matrix)){
                    if (!letterInsert(k, l, matrix)) {
                        if(l>0) l--;
                        else if (k>0) {
                            k--;
                            l=colN-1;
                        }
                    }
                }
                
            } 
        }
    }
}

