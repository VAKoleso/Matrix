#include "s21_matrix.h"

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t tmp;
  tmp.matrix = (double **)malloc(rows * sizeof(double *));

  for (int i = 0; i < rows; i++) {
    tmp.matrix[i] = (double *)malloc(columns * sizeof(double *));
  }

  tmp.rows = rows;
  tmp.columns = columns;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      tmp.matrix[i][j] = 0.0;
    }
  }
  tmp.matrix_type = 3;
  if (rows < 1 || columns < 1) {
    tmp.matrix_type = INCORRECT_MATRIX;
  }
  return tmp;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int tmp = TRUE;
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows && tmp == TRUE; i++) {
      for (int j = 0; j < A->columns && tmp == TRUE; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.000001) {
          tmp = FALSE;
        }
      }
    }
  } else {
    tmp = FALSE;
  }
  return tmp;
}

void s21_set_valuetype_matrix(matrix_t *A) {
  A->matrix_type = ZERO_MATRIX;
  for (int i = 0; i < A->rows && A->matrix_type == ZERO_MATRIX; i++) {
    for (int j = 0; j < A->columns && A->matrix_type == ZERO_MATRIX; j++) {
      if (A->matrix[i][j] != 0.0) {
        A->matrix_type = CORRECT_MATRIX;
      }
    }
  }
  if (A->matrix_type != ZERO_MATRIX && A->rows == A->columns) {
    A->matrix_type = IDENTITY_MATRIX;
    for (int i = 0; i < A->rows && A->matrix_type == IDENTITY_MATRIX; i++) {
      for (int j = 0; j < A->columns && A->matrix_type == IDENTITY_MATRIX;
           j++) {
        if ((i == j && A->matrix[i][j] != 1.0) ||
            (i != j && A->matrix[i][j] != 0.0))
          A->matrix_type = CORRECT_MATRIX;
      }
    }
  }
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
  matrix_t res;
  res = s21_create_matrix(A->rows, A->columns);
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        res.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
    s21_set_valuetype_matrix(&res);
  } else {
    res.matrix_type = INCORRECT_MATRIX;
  }
  return res;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
  matrix_t res;
  res = s21_create_matrix(A->rows, A->columns);
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        res.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
    s21_set_valuetype_matrix(&res);
  } else {
    res.matrix_type = INCORRECT_MATRIX;
  }
  return res;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
  matrix_t res;
  res = s21_create_matrix(A->rows, A->columns);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      res.matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  s21_set_valuetype_matrix(&res);
  return res;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
  matrix_t res;
  res = s21_create_matrix(A->rows, B->columns);
  if (B->rows == A->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        res.matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          res.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
    s21_set_valuetype_matrix(&res);
  } else {
    res.matrix_type = INCORRECT_MATRIX;
  }
  return res;
}

matrix_t s21_transpose(matrix_t *A) {
  matrix_t res;
  res = s21_create_matrix(A->columns, A->rows);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      res.matrix[j][i] = A->matrix[i][j];
    }
  }
  s21_set_valuetype_matrix(&res);
  return res;
}

matrix_t s21_minor_matrix(matrix_t A, int row, int column) {
  matrix_t res;
  res = s21_create_matrix(A.rows - 1, A.columns - 1);

  int x = 0, y = 0;
  for (int i = 0; i < A.rows; i++) {
    if (i != row) {
      for (int j = 0; j < A.columns; j++) {
        if (j != column) {
          res.matrix[x][y] = A.matrix[i][j];
          y++;
        }
      }
      x++;
      y = 0;
    }
  }
  return res;
}

double pew(int y) {
  double x = 1;
  while (y) {
    x *= -1;
    y--;
  }
  return x;
}

matrix_t s21_calc_complements(matrix_t *A) {
  matrix_t res;
  res = s21_create_matrix(A->rows, A->columns);
  matrix_t tmp;
  if (A->rows == A->columns && A->rows > 1) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        tmp = s21_minor_matrix(*A, i, j);
        res.matrix[i][j] = pew(i + j) * determinant(&tmp);
        s21_remove_matrix(&tmp);
      }
    }
    s21_set_valuetype_matrix(&res);
  } else {
    res.matrix_type = INCORRECT_MATRIX;
  }
  return res;
}

double s21_determinant(matrix_t *A) {
  double res = 0;
  if (A->rows == A->columns)
    res = determinant(A);
  else
    res = NAN;
  return res;
}
double determinant(matrix_t *A) {
  matrix_t tmp;
  double res = 0;
  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else if (A->rows == 2) {
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
      tmp = s21_minor_matrix(*A, i, 0);
      res += sign * A->matrix[i][0] * determinant(&tmp);
      sign *= -1;
      s21_remove_matrix(&tmp);
    }
  }
  return res;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
  matrix_t res;
  res = s21_create_matrix(A->rows, A->columns);
  if (A->rows == A->columns && A->rows > 1) {
    double determinante = s21_determinant(A);
    if (determinante != 0.0) {
      matrix_t tmp;
      matrix_t tmp1;
      matrix_t tmp2;
      tmp = s21_calc_complements(A);
      tmp1 = s21_transpose(&tmp);
      tmp2 = s21_mult_number(&tmp1, 1.0 / determinante);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          res.matrix[i][j] = tmp2.matrix[i][j];
        }
      }
      s21_remove_matrix(&tmp);
      s21_remove_matrix(&tmp1);
      s21_remove_matrix(&tmp2);
      s21_set_valuetype_matrix(&res);
    } else {
      res.matrix_type = INCORRECT_MATRIX;
    }
  } else {
    res.matrix_type = INCORRECT_MATRIX;
  }
  return res;
}
