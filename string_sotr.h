#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "str_fun.h"

typedef int (comparator)(void* const first_element, void* const second_element, const size_t size);

#define MATRIX_IND(x, size_y) ((x) * (size_y))
#define MANUAL_IND(cnt_blocks, size_blocks, arr) ((size_t)(arr) + (cnt_blocks) * (size_blocks))
#define ASSIGN_BLOCK(type) while (num_block++ < size) *((type*)lhs + num_block) = *((type*)rhs + num_block);

static error_code_e LAST_ERROR_CODE = INIT_VALUE;

error_code_e swap_symbol_by_symbol    (char* first_str, char* second_str,      const size_t size);
error_code_e swap_all_strings         (char* first_str, char* second_str,      const size_t size);
error_code_e swap_with_ll_buffer      (char* first_str, char* second_str,      const size_t size);


error_code_e bubble_sort   (char* str_array, const size_t size_x, const size_t size_y); // TODO проверка отсортированности
error_code_e selection_sort(char* str_array, const size_t size_x, const size_t size_y);
error_code_e merge_sort    (const void* str_array, const size_t size_x, const size_t left,  const size_t right, comparator cmp);

error_code_e merge     (const void* const first_arr,     const size_t first_size,          const void* const second_arr, const size_t second_size, void* const result_arr, size_t result_size, comparator cmp);
error_code_e assignment(void* const lhs,                 void* const rhs,                  const size_t size,            const size_t size_type);
int ptr_str_cmp        (void* const first_element,       void* const second_element,       const size_t size);
error_code_e copy_arr  (void* const lhs,                 void* const rhs,                  const size_t size);

// error_code_e test_bubble_sort   ();
// error_code_e test_selection_sort();
error_code_e test_merge_sort    ();
