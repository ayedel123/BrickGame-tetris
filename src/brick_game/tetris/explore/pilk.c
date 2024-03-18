#include <stdio.h>
#include <stdlib.h>


void drawField( int **field, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j]) {
                printf(" ");
            } else {
                printf("0");
            }
        }
    }
}

int main(){
int rows = 100;
int cols = 100;
   int** field = (int**)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; i++) {
        field[i] = (int*)calloc(cols, sizeof(int));
    }
    drawField(field,rows,cols);
    return 0;
}

