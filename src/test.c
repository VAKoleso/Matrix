#include <check.h>

#include "s21_matrix.h"

START_TEST(create1) {
  matrix_t A;
  int rows = 5, columns = 7;
  A = s21_create_matrix(rows, columns);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) ck_assert_uint_eq(A.matrix[i][j], 0.0);
  ck_assert_int_eq(A.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create2) {
  matrix_t A;
  A = s21_create_matrix(-1, -1);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) ck_assert_uint_eq(A.matrix[i][j], 0.0);
  ck_assert_int_eq(A.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq1) {
  matrix_t A;
  matrix_t B;
  A = s21_create_matrix(4, 4);
  B = s21_create_matrix(4, 4);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(TRUE, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq2) {
  matrix_t A;
  matrix_t B;
  A = s21_create_matrix(4, 4);
  B = s21_create_matrix(4, 4);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i - j;
    }
  }
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FALSE, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq3) {
  matrix_t A;
  matrix_t B;
  A = s21_create_matrix(4, 4);
  B = s21_create_matrix(3, 2);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j;
    }
  }
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = i + j;
    }
  }
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FALSE, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum1) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  double ret = 0.0;
  matrix_t res = s21_sum_matrix(&A, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret, res.matrix[i][j]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum2) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  matrix_t res;
  double ret[] = {3, 3, 3, 3, 5, 5, 5, 5, 7, 7, 7, 7, 9, 9, 9, 9};
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + 1;
      B.matrix[i][j] = i + 2;
    }
  }
  res = s21_sum_matrix(&A, &B);
  for (int i = 0, k = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret[k], res.matrix[i][j]);
      k++;
    }
  }
  ck_assert_int_eq(res.matrix_type, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum3) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(3, 3);
  matrix_t res;

  res = s21_sum_matrix(&A, &B);

  ck_assert_int_eq(res.matrix_type, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub1) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  double ret = 0.0;
  matrix_t res = s21_sub_matrix(&A, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret, res.matrix[i][j]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub2) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  matrix_t res;
  double ret = 1;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + 2;
      B.matrix[i][j] = i + 1;
    }
  }
  res = s21_sub_matrix(&A, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret, res.matrix[i][j]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub3) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(3, 3);
  matrix_t res;

  res = s21_sub_matrix(&A, &B);

  ck_assert_int_eq(res.matrix_type, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult1) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  double ret = 0.0;
  matrix_t res = s21_mult_matrix(&A, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret, res.matrix[i][j]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult2) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  matrix_t res;
  double ret[] = {20, 20, 20, 20, 30, 30, 30, 30,
                  40, 40, 40, 40, 50, 50, 50, 50};
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + 2;
      B.matrix[i][j] = i + 1;
    }
  }
  res = s21_mult_matrix(&A, &B);
  for (int i = 0, k = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret[k], res.matrix[i][j]);
      k++;
    }
  }
  ck_assert_int_eq(res.matrix_type, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult3) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(3, 3);
  matrix_t res;

  res = s21_mult_matrix(&A, &B);

  ck_assert_int_eq(res.matrix_type, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_number1) {
  matrix_t A = s21_create_matrix(4, 4);
  double ret = 0.0;
  matrix_t res = s21_mult_number(&A, 5);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret, res.matrix[i][j]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_number2) {
  matrix_t A = s21_create_matrix(4, 4);
  double ret[] = {4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 8, 8, 10, 10, 10, 10};
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + 2;
    }
  }
  matrix_t res = s21_mult_number(&A, 2);
  for (int i = 0, k = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret[k], res.matrix[i][j]);
      k++;
    }
  }
  ck_assert_int_eq(res.matrix_type, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(transpose1) {
  matrix_t A = s21_create_matrix(4, 2);
  matrix_t res;
  matrix_t ret = s21_create_matrix(2, 4);
  res = s21_transpose(&A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret.matrix[j][i], res.matrix[j][i]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&ret);
}
END_TEST

START_TEST(transpose2) {
  matrix_t A = s21_create_matrix(4, 2);
  matrix_t res;
  matrix_t ret = s21_create_matrix(2, 4);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + 2;
      ret.matrix[j][i] = i + 2;
    }
  }
  res = s21_transpose(&A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(ret.matrix[j][i], res.matrix[j][i]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&ret);
}
END_TEST

START_TEST(calc1) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t res;
  matrix_t ret = s21_create_matrix(3, 3);
  res = s21_calc_complements(&A);
  for (int i = 0; i < res.rows; i++) {
    for (int j = 0; j < res.columns; j++) {
      ck_assert_uint_eq(A.matrix[i][j], res.matrix[i][j]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&ret);
}
END_TEST

START_TEST(calc2) {
  matrix_t A = s21_create_matrix(3, 3);
  double ret[] = {-3, 6, -3, 6, -12, 6, -3, 6, -3};
  matrix_t res;
  for (int i = 0, k = 1; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = k + 1;
      k++;
    }
  }
  res = s21_calc_complements(&A);
  for (int i = 0, k = 0; i < res.rows; i++) {
    for (int j = 0; j < res.columns; j++) {
      ck_assert_uint_eq(ret[k], res.matrix[i][j]);
      k++;
    }
  }
  ck_assert_int_eq(res.matrix_type, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc3) {
  matrix_t A;
  matrix_t res;
  A = s21_create_matrix(1, 1);
  res = s21_calc_complements(&A);
  ck_assert_int_eq(res.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc4) {
  matrix_t A;
  matrix_t res;
  A = s21_create_matrix(1, 4);
  res = s21_calc_complements(&A);
  ck_assert_int_eq(res.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(determ1) {
  matrix_t A;
  double determinate = 0;
  int check = 0;
  A = s21_create_matrix(3, 1);
  determinate = s21_determinant(&A);
  if (isnan(determinate) != 0) check = 1;
  ck_assert_int_eq(1, check);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determ2) {
  matrix_t A = s21_create_matrix(3, 3);
  double res;
  for (int i = 0, k = 1; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = k + 1;
      k++;
    }
  }
  res = determinant(&A);
  ck_assert_uint_eq(0, res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determ3) {
  matrix_t A = s21_create_matrix(1, 1);
  double res;
  for (int i = 0, k = 1; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = k + 1;
      k++;
    }
  }
  res = determinant(&A);
  ck_assert_uint_eq(2, res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse1) {
  matrix_t A;
  matrix_t res;
  A = s21_create_matrix(2, 3);
  res = s21_inverse_matrix(&A);
  ck_assert_int_eq(res.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse2) {
  matrix_t A;
  matrix_t res;
  A = s21_create_matrix(1, 1);
  A.matrix[0][0] = 545;
  res = s21_inverse_matrix(&A);
  ck_assert_int_eq(res.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse3) {
  matrix_t A;
  matrix_t res;
  A = s21_create_matrix(3, 3);
  double test[] = {0, -0.1, 0.2, -0.25, 0.35, 0.05, 0.5, -0.2, -0.1};
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  res = s21_inverse_matrix(&A);
  for (int i = 0, k = 0; i < res.rows; i++) {
    for (int j = 0; j < res.columns; j++) {
      ck_assert_uint_eq(res.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(res.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse4) {
  matrix_t A = s21_create_matrix(1, 1);
  matrix_t res;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 0;
    }
  }
  res = s21_inverse_matrix(&A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_uint_eq(0, res.matrix[i][j]);
    }
  }
  ck_assert_int_eq(res.matrix_type, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("fpeEGg");
  SRunner *sr = srunner_create(s1);
  int nf;

  TCase *tc1_1 = tcase_create("fpeEGg");
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, create1);
  tcase_add_test(tc1_1, create2);
  tcase_add_test(tc1_1, eq1);
  tcase_add_test(tc1_1, eq2);
  tcase_add_test(tc1_1, eq3);
  tcase_add_test(tc1_1, sum1);
  tcase_add_test(tc1_1, sum2);
  tcase_add_test(tc1_1, sum3);
  tcase_add_test(tc1_1, sub1);
  tcase_add_test(tc1_1, sub2);
  tcase_add_test(tc1_1, sub3);
  tcase_add_test(tc1_1, mult1);
  tcase_add_test(tc1_1, mult2);
  tcase_add_test(tc1_1, mult3);
  tcase_add_test(tc1_1, mult_number1);
  tcase_add_test(tc1_1, mult_number2);
  tcase_add_test(tc1_1, transpose1);
  tcase_add_test(tc1_1, transpose2);
  tcase_add_test(tc1_1, calc1);
  tcase_add_test(tc1_1, calc2);
  tcase_add_test(tc1_1, calc3);
  tcase_add_test(tc1_1, calc4);
  tcase_add_test(tc1_1, determ1);
  tcase_add_test(tc1_1, determ2);
  tcase_add_test(tc1_1, determ3);
  tcase_add_test(tc1_1, inverse1);
  tcase_add_test(tc1_1, inverse2);
  tcase_add_test(tc1_1, inverse3);
  tcase_add_test(tc1_1, inverse4);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
