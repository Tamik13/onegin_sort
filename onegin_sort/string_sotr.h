#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "str_fun.h"

typedef int (comparator)(const void* first_element, const void* second_element);

#define MATRIX_IND(x, size_y) ((x) * (size_y))
#define MANUAL_IND(block, arr) ((char* const)(arr) + (block))
#define ASSIGN_BLOCK(type) while (num_block++ < size) *((type*)lhs + num_block) = *((type*)rhs + num_block);

error_code_e swap_symbol_by_symbol(char* first_str, char* second_str, const size_t size);
error_code_e swap_all_strings     (char* first_str, char* second_str, const size_t size);
error_code_e swap_with_ll_buffer  (char* first_str, char* second_str, const size_t size);


error_code_e bubble_sort   (char* str_array,       const size_t size, const size_t size_y);
error_code_e selection_sort(char* const str_array, const size_t size, const size_t size_y);
error_code_e q_sort        (void* const array,     const size_t size, const size_t type_size, comparator cmp);
error_code_e merge_sort    (void* const str_array, const size_t size, comparator cmp);

error_code_e merge     (const void* const first_arr,     const size_t first_size,          const void* const second_arr, const size_t second_size, void* const result_arr, const size_t result_size, comparator cmp);
error_code_e copy_arr  (const void* const lhs,           const void* const rhs,            const size_t size);

int string_cmp(const void* const first_str,     const void* const second_str);
int int_cmp   (const void* const first_element, const void* const second_element);

error_code_e test_bubble_sort   ();
error_code_e test_selection_sort();
error_code_e test_q_sort        ();
error_code_e test_merge_sort    ();
