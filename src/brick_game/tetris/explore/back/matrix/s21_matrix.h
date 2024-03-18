#ifndef _S21_MATRIX_H_
#define _S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../bricks.h"

#define OK 0
#define ERROR 1
#define CALCULATION_ERROR 2

#define INVALID_MATRIX 1
#define EPSILON 1e-07

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  int **matrix;
  int rows;
  int columns;
} matrix_t;
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void copy_matrix(matrix_t *src, matrix_t *dest);
#endif  // _S21_MATRIX_H_