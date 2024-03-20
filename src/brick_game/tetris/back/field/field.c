#include "field.h"

void clearField(int **field, int rows, int cols) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      field[i][j] = 0;
    }
  }
}

void deleteField(int **field, int rows) {

  for (int i = 0; i < rows; i++) {
    free(field[i]);
  }
  free(field);
}

int initField(int ***field, int rows, int cols) {
  *field = (int **)calloc(rows, sizeof(int *));
  for (int i = 0; i < rows; i++) {
    (*field)[i] = (int *)calloc(cols, sizeof(int));
  }
  return 0;
}