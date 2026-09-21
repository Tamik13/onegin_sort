#include "debuging.h"

// error_code_e get_random_int_arr();
// error_code_e get_random_string ();
//
// error_code_e get_random_int ();
// error_code_e get_random_char();



void $print_strptr_arr(const char* const arr[], const size_t size) {
    assert(arr != NULL);

    for (size_t block_ind = 0; block_ind < size; block_ind++) {
        ASSERT_FOR_ARR(block_ind, size);
        printf("<%s>\n", arr[block_ind]);
    }
}


void $print_str_matrix(const char* const arr, const size_t size_x, const size_t size_y) {
    assert(arr != NULL);

    for (size_t x = 0; x < size_x; x++) {
        ASSERT_FOR_ARR(x, size_x);
        printf("<%s>\n", ((arr + size_y * x)));
    }
}


void $print_int_arr(const int int_array[], const size_t size) {
    assert(int_array != NULL);

    for (size_t x = 0; x < size; x++) {
        ASSERT_FOR_ARR(x, size);
        printf("%d", int_array[x]);
    }
}


void $print_intptr_arr(const int* const int_array[], const size_t size) {
    assert(int_array != NULL);

    for (size_t x = 0; x < size; x++) {
        ASSERT_FOR_ARR(x, size);

        printf("%d ", *int_array[x]);
    }
    printf("\n");
}



