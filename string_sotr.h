#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "str_fun.h"

#define MATRIX_IND(x, y) (x * size_y)
#define MANUAL_IND(bytes, arr) ((size_t)arr + bytes * sizeof(char))

static error_code_e LAST_ERROR_CODE = INIT_VALUE;

error_code_e swap_symbol_by_symbol(char* first_str, char* second_str, const size_t size);
error_code_e swap_all_strings     (char* first_str, char* second_str, const size_t size);
error_code_e swap_with_ll_buffer  (char* first_str, char* second_str, const size_t size);

error_code_e bubble_sort   (char* str_array, const size_t size_x, const size_t size_y); // TODO проверка отсортированности
error_code_e selection_sort(char* str_array, const size_t size_x, const size_t size_y);
error_code_e merge_sort    (char* str_array, const size_t size_x, const size_t left,  const size_t right);

error_code_e print_str_matrix(const char* const str_array, const size_t size_x, const size_t size_y);

error_code_e merge   (char* first_arr, size_t first_size, char* second_arr, size_t second_size, char* result_arr, size_t result_size);
error_code_e copy_arr(char* first_arr[], size_t first_size, char* second_arr[], size_t second_size);

error_code_e test_bubble_sort();
error_code_e test_selection_sort();
error_code_e test_merge_sort();
