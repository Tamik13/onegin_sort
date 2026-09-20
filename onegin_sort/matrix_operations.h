#include <stdio.h>
#include <assert.h>
#include "debuging.h"

#define TRIANGULAR_MATRIX_CNT_ELEMENTS(size) (((size_t)size + 1) * (size_t)size / 2)
#define TRIANGULAR_MATRIX_IND(x, y)          (TRIANGULAR_MATRIX_CNT_ELEMENTS(x) + (size_t)y)
#define MATRIX_IND(x, y, size_y)             ((size_t)x * size_y + (size_t)y)

error_code_e sum_matrices           (const int* const first_matrix, const int* const second_matrix, int* const result_matrix,   const size_t size_x,       const size_t size_y);
error_code_e multiplication_matrices(const int* const first_matrix, const int* const second_matrix, int* const result_matrix,   const size_t size_x_first, const size_t size_y_first,
                                     const size_t size_x_second,    const size_t size_y_second,     const size_t size_x_result, const size_t size_y_result);

error_code_e print_matrix           (int* const matrix, const size_t size_x, const size_t size_y);
error_code_e print_triangular_matrix(int* const matrix, const size_t size);

error_code_e test_matrix_functions();
