#include "debuging.h"

// error_code_e get_random_int_arr();
// error_code_e get_random_string ();
//
// error_code_e get_random_int ();
// error_code_e get_random_char();


error_code_e print_str_matrix(const char* const arr[], const size_t size) {
    assert(arr != NULL);

    for (size_t block_ind = 0; block_ind < size; block_ind++) {
        ASSERT_FOR_ARR(block_ind, size);
        printf("<%s>\n", arr[block_ind]);
    }

    return SUCCESS;
}

error_code_e print_int_arr(const int int_array[], const size_t size_x) {
    assert(int_array != NULL);

    for (size_t x = 0; x < size_x; x++) {
        ASSERT_FOR_ARR(x, size_x);
        printf("%d", int_array[x]);
    }

    return SUCCESS;
}

error_code_e print_int_matrix(const int int_array[], const size_t size_x, const size_t size_y) {
    assert(int_array != NULL);

    for (size_t x = 0; x < size_x; x++) {
        for (size_t y = 0; y < size_y; y++) {
            ASSERT_FOR_ARR(x * size_y + y, size_x * size_y);
            printf("%d ", int_array[x * size_y + y]);
        }
    }

    return SUCCESS;
}

error_code_e print_intptr_arr(const int* const int_array[], const size_t size) {
    assert(int_array != NULL);

    // $ANCHOR

    // PRINT_PTR_ARR(int_array, size);

    for (size_t x = 0; x < size; x++) {
        ASSERT_FOR_ARR(x, size);

        printf("%d ", *int_array[x]);
    }
    printf("\n");

    return SUCCESS;
}



