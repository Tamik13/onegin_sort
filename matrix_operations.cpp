#include "matrix_operations.h"

static error_code_e LAST_ERROR_CODE = INIT_VALUE;

error_code_e sum_matrices           (const int* const first_matrix, const int* const second_matrix, int* const result_matrix,   const size_t size_x,       const size_t size_y);
error_code_e multiplication_matrices(const int* const first_matrix, const int* const second_matrix, int* const result_matrix,   const size_t size_x_first, const size_t size_y_first,
                                     const size_t size_x_second,    const size_t size_y_second,     const size_t size_x_result, const size_t size_y_result);

error_code_e print_matrix           (int* const matrix, const size_t size_x, const size_t size_y);
error_code_e print_triangular_matrix(int* const matrix, const size_t size);

error_code_e test_matrix_functions();

error_code_e sum_matrices(const int* const first_matrix, const int* const second_matrix, int* const result_matrix, const size_t size_x, const size_t size_y) {
    assert(first_matrix != NULL);
    assert(second_matrix != NULL);
    assert(result_matrix != NULL);

    for (size_t x = 0; x < size_x; x++) {
        for (size_t y = 0; y < size_y; y++) {
            const size_t IND = MATRIX_IND(x, y, size_y);
            ASSERT_FOR_ARR(IND, size_x * size_y);

            result_matrix[IND] = first_matrix[IND] + second_matrix[IND];
        }
    }

    return SUCCESS;
}

error_code_e multiplication_matrices(const int* const first_matrix, const int* const second_matrix, int* const result_matrix,   const size_t size_x_first, const size_t size_y_first,
                                     const size_t size_x_second,    const size_t size_y_second,     const size_t size_x_result, const size_t size_y_result) {
    assert(first_matrix != NULL);
    assert(second_matrix != NULL);
    assert(result_matrix != NULL);

    if (size_y_first != size_x_second || size_x_first != size_x_result || size_y_second != size_y_result) {
        PRINT_ERROR;
        // TODO log file
        return INCORRECT_MATRIX_SIZE;
    }

    for (size_t x = 0; x < size_x_first; x++) {
        for (size_t y = 0; y < size_y_first; y++) {
            ASSERT_FOR_ARR(MATRIX_IND(x, y, size_y_first), size_x_first * size_y_first);
            result_matrix[MATRIX_IND(x, y, size_y_first)] = 0;
        }
    }

    for (size_t x = 0; x < size_x_first; x++) {
        for (size_t y = 0; y < size_y_second; y++) {
            for (size_t el = 0; el < size_y_first; el++) {
                ASSERT_FOR_ARR(MATRIX_IND(x, y, size_y_first), size_x_first * size_y_second);
                ASSERT_FOR_ARR(MATRIX_IND(x, el, size_y_first), size_x_first * size_y_first);
                ASSERT_FOR_ARR(MATRIX_IND(el, y, size_y_second), size_x_second * size_y_second);

                result_matrix[MATRIX_IND(x, y, size_y_first)] += first_matrix[MATRIX_IND(x, el, size_y_first)] * second_matrix[MATRIX_IND(el, y, size_y_second)];
            }
        }
    }

    return SUCCESS;
}

error_code_e print_matrix(int* matrix, const size_t size_x, const size_t size_y) {
    assert(matrix != NULL);

    for (size_t x = 0; x < size_x; x++) {
        for (size_t y = 0; y < size_y; y++) {
            ASSERT_FOR_ARR(x, size_x);
            ASSERT_FOR_ARR(y, size_y);

            printf("[%zu][%zu] = %d   ", x, y, matrix[MATRIX_IND(x, y, size_y)]);
        }
        printf("\n");
    }

    return SUCCESS;
}

error_code_e print_triangular_matrix(int* const matrix, const size_t size) {
    assert(matrix != NULL);

    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y <= x; y++) {
            ASSERT_FOR_ARR(TRIANGULAR_MATRIX_IND(x, y), TRIANGULAR_MATRIX_CNT_ELEMENTS(size));

            printf("[%zu][%zu] = %d  ", x, y, matrix[TRIANGULAR_MATRIX_IND(x, y)]);
        }
        printf("\n");
    }

    return SUCCESS;
}

error_code_e test_matrix_functions() {
    const size_t size_x_first = 2;
    const size_t size_y_first = 3;

    int first_matrix[size_x_first * size_y_first] = {
        1, 2, -1,
        0, 4, 1
    };

    const size_t size_x_second = 3;
    const size_t size_y_second = 3;

    int second_matrix[size_x_second * size_y_second] = {
        0, -1, -2,
        1, -3, 3,
        -2, 3, 3
    };

    int result_matrix[size_x_first * size_y_second] = {};

    const size_t triangular_size = 4;

    int triangular_matrix[TRIANGULAR_MATRIX_CNT_ELEMENTS(triangular_size)] = {
        1,
        2, 3,
        4, 5, 6,
        7, 8, 9, 10
    };

    if ((LAST_ERROR_CODE = multiplication_matrices(first_matrix,  second_matrix, result_matrix, size_x_first, size_y_first,
                                                   size_x_second, size_y_second, size_x_first,  size_y_second)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }


    if ((LAST_ERROR_CODE = print_matrix(result_matrix, size_x_first, size_y_second)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    printf("\n");

    if ((LAST_ERROR_CODE = print_triangular_matrix(triangular_matrix, triangular_size)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    return SUCCESS;
}

