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
        for (j=0; j<NSIZE; j++) {
            matrix[i][j].possibleValues = (char *) malloc (sizeof(char) * NSIZE+1);
            matrix[i][j].nPossible=0;
        }
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
//Check if character can be added to this position
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
    quadrantLine=line - line % 4;
    quadrantColumn= col - col % 4;
    for (i=quadrantLine; i<quadrantLine+4; i++) {
        for (j=quadrantColumn; j< quadrantColumn+4; j++) {
            if (matrix[i][j].symbol == symbol) return 0;
        }
    }
    return 1;
}

//Finds the next empty spot to add a value
int findEmpty(int *line, int *col, MATRIX_ELEM **matrix) {
    int i, j;
    for (i=0; i<NSIZE; i++) {
        for (j=0; j<NSIZE; j++) {
            if (matrix[*line][*col].symbol == '.') {
                return 1;
            }
            *col += 1;
        }
        *line += 1;
    }
    return 0;
}
//Finds the spots where there is only one possible solution
//When a spot with only one solution is found, it calls the function "checkPossible" to calculate again the possible solutions for all cells
//and then it looks again for cells with only one possible solution, now considering the new value that has been added in previous step.
void findUniqueSolution(MATRIX_ELEM **matrix, char *alfaHex) {
    int i, j;
    int foundUnique=1;
    while (foundUnique) {
        foundUnique=0;
        for (i=0; i<NSIZE; i++) {
            for (j=0; j<NSIZE; j++) {
                if (matrix[i][j].nPossible == 1) {
                    matrix[i][j].symbol = matrix[i][j].possibleValues[0];
                    checkPossible(matrix, alfaHex);
                    foundUnique=1;
                }
            }
        }
    }
}

//Check and store the possible solutions for modifiable spots
void checkPossible(MATRIX_ELEM **matrix, char *alfaHex) {
    int i, j, k;
    for (i=0; i<NSIZE; i++) {
        for (j=0; j<NSIZE; j++) {
            matrix[i][j].nPossible=0;
            if (isBlankSpace(i, j, matrix)) {
                for (k=0; k<NSIZE; k++) {
                    if (posValidator(alfaHex[k], i, j, matrix)) {
                        matrix[i][j].possibleValues[matrix[i][j].nPossible]=alfaHex[k];
                        matrix[i][j].nPossible++;
                    }
                }
            }
        }

    }
}

//Recursive function that allows backtracking to solve sudoku
//It goes forward through cells, finding the solutions. If the process gets stuck, it takes one step back and try with other values
int solve(MATRIX_ELEM **matrix) {
    int auxChar;
    int line=0, col=0;
    if (!findEmpty(&line, &col, matrix)){
        return 1;
    } 
    for (auxChar=0; auxChar<matrix[line][col].nPossible; auxChar++) {
        if (posValidator(matrix[line][col].possibleValues[auxChar], line, col, matrix)) {
            matrix[line][col].symbol = matrix[line][col].possibleValues[auxChar];
            if (solve(matrix)) return 1;
            else matrix[line][col].symbol ='.';
        }
        
    }
    return 0;
}

