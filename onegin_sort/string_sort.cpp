#include "string_sotr.h"

const size_t MAX_STR_LEN = 100;
static error_code_e LAST_ERROR_CODE = INIT_VALUE;

error_code_e swap_symbol_by_symbol(char* first_str, char* second_str, const size_t size) {
    assert(first_str  != NULL);
    assert(second_str != NULL);

    for (size_t i = 0; (first_str[i] != '\0' || second_str[i] != '\0') && i < size; i++) {
        ASSERT_FOR_ARR(i, size);

        char buffer = first_str[i];
        first_str[i] = second_str[i];
        second_str[i] = buffer;
    }

    return SUCCESS;
}


error_code_e swap_all_strings(char* first_str, char* second_str, const size_t size) {
    assert(first_str  != NULL);
    assert(second_str != NULL);

    char* buffer = (char*)calloc(size, sizeof(char));

    for (size_t x = 0; x < size; x++) {
        ASSERT_FOR_ARR(x, size);
        buffer[x] = first_str[x];
    }

    for (size_t x = 0; x < size; x++) {
        ASSERT_FOR_ARR(x, size);
        first_str[x] = second_str[x];
    }

    for (size_t x = 0; x < size; x++) {
        ASSERT_FOR_ARR(x, size);
        second_str[x] = buffer[x];
    }

    free(buffer);

    return SUCCESS;
}


error_code_e swap_with_ll_buffer(char* first_str, char* second_str, const size_t size) {
    assert(first_str  != NULL);
    assert(second_str != NULL);

    size_t   ind = 0;
    uint64_t buffer = 0;

    while (size - ind >= sizeof(uint64_t)) {
        ASSERT_FOR_ARR(ind, size);

        memcpy(&buffer,          first_str  + ind, sizeof(uint64_t));
        memcpy(first_str  + ind, second_str + ind, sizeof(uint64_t));
        memcpy(second_str + ind, &buffer,          sizeof(uint64_t));

        ind += sizeof(uint64_t);
    }

    while (size - ind >= sizeof(uint32_t)) {
        ASSERT_FOR_ARR(ind, size);

        memcpy(&buffer,          first_str  + ind, sizeof(uint32_t));
        memcpy(first_str  + ind, second_str + ind, sizeof(uint32_t));
        memcpy(second_str + ind, &buffer,          sizeof(uint32_t));

        ind += sizeof(uint32_t);
    }

    while (size - ind >= sizeof(uint16_t)) {
        ASSERT_FOR_ARR(ind, size);

        memcpy(&buffer,          first_str  + ind, sizeof(uint16_t));
        memcpy(first_str  + ind, second_str + ind, sizeof(uint16_t));
        memcpy(second_str + ind, &buffer,          sizeof(uint16_t));

        ind += sizeof(uint16_t);
    }

    while (size - ind >= sizeof(uint8_t)) {
        ASSERT_FOR_ARR(ind, size);

        memcpy(&buffer,          first_str + ind,  sizeof(uint8_t));
        memcpy(first_str + ind,  second_str + ind, sizeof(uint8_t));
        memcpy(second_str + ind, &buffer,          sizeof(uint8_t));

        ind += sizeof(uint8_t);
    }

    return SUCCESS;
}


error_code_e bubble_sort(char* str_array, const size_t size_x, const size_t size_y) {
    assert(str_array != NULL);

    for (size_t x = 0; x < size_x; x++) {
        for (size_t y = 0; y < size_x - x - 1; y++) {
            ASSERT_FOR_ARR(x, size_x);
            ASSERT_FOR_ARR(y, size_x);

            if (y == x) continue;

            if (my_strncmp(&str_array[y * size_y], &str_array[(y + 1) * size_y], size_y) > 0) {
                swap_with_ll_buffer(&str_array[y * size_y], &str_array[(y + 1) * size_y], size_y);
            }
        }
    }

    return SUCCESS;
}


error_code_e selection_sort(char* str_array, const size_t size_x, const size_t size_y) {
    assert(str_array != NULL);

    for (size_t x = 0; x < size_x; x++) {
        size_t min = x;
        for (size_t y = x; y < size_x; y++) {
            if (my_strncmp(&str_array[MATRIX_IND(y, size_y)], &str_array[MATRIX_IND(min, size_y)], size_y) < 0) {
                min = y;
            }
        }
        swap_all_strings(&str_array[MATRIX_IND(min, size_y)], &str_array[MATRIX_IND(x, size_y)], size_y);
    }

    return SUCCESS;
}

error_code_e q_sort(int* const array, const size_t size) {
    assert(array != NULL);
    // assert(size  != 0);

    $START_FUNCTION;

    if (size <= 1) {
        $END_FUNCTION
        return SUCCESS;
    }

    size_t left   = 0;
    size_t right  = size - 1;
    size_t middle_el = array[size / 2];

    while (left < right) {

        while (left <= right && array[left] < middle_el) {
            left++;
            $DEBUG_QSORT
        }

        while (left <= right && middle_el   < array[right]) {
            right--;
            $DEBUG_QSORT
        }

        if (left < right) {
            swap_with_ll_buffer((char*)&array[left], (char*)&array[right], sizeof(int));
            left++;
            $ANCHOR
            $DEBUG_QSORT

            if (left < right) {
                right--;
                $DEBUG_QSORT
            }
        }

    }
    $DEBUG_QSORT

    q_sort(array, left);
    $DEBUG_QSORT
    q_sort(array + left, size - left);

    $DEBUG_QSORT

    $END_FUNCTION

    return SUCCESS;
}


error_code_e merge_sort(void* const array, const size_t size, comparator cmp) {
    assert(array != NULL);

    if (size <= 1) {
        return SUCCESS;
    }

    size_t middle = size / 2;

    void* left_array  = (void**)array;
    void* right_array = (void**)array + middle;

    const size_t left_size  = middle;
    const size_t right_size = size - middle;

    merge_sort(left_array,  left_size,  cmp);
    merge_sort(right_array, right_size,  cmp);

    merge(left_array, left_size, right_array, right_size, array, size, cmp);

    return SUCCESS;
}


error_code_e merge(const void* const first_arr, const size_t first_size, const void* const second_arr, const size_t second_size, void* const result_arr, const size_t result_size, comparator cmp) {
    assert(first_arr  != NULL);
    assert(second_arr != NULL);
    assert(first_size + second_size == result_size);

    void* const first_arr_copy  = calloc(first_size,  sizeof(size_t));
    void* const second_arr_copy = calloc(second_size, sizeof(size_t));

    memcpy(first_arr_copy,  first_arr,  first_size  * sizeof(size_t));
    memcpy(second_arr_copy, second_arr, second_size * sizeof(size_t));

    assert(first_arr_copy != NULL);
    assert(second_arr_copy != NULL);

    size_t first_ind = 0, second_ind = 0;

    while (first_ind < first_size && second_ind < second_size) {
        ASSERT_FOR_ARR(first_ind,  first_size);
        ASSERT_FOR_ARR(second_ind, second_size);
        ASSERT_FOR_ARR(first_ind + second_ind, result_arr);

        const void* const first_element_ptr  = (const void* const)((const size_t* const)first_arr_copy  + first_ind);
        const void* const second_element_ptr = (const void* const)((const size_t* const)second_arr_copy + second_ind);
              void* const result_element_ptr = (void* const)((const size_t* const)result_arr + first_ind + second_ind);

        const void* const first_element  = (const void* const)*((const size_t* const)first_element_ptr);
        const void* const second_element = (const void* const)*((const size_t* const)second_element_ptr);

        $ANCHOR

        int comparison = cmp(first_element, second_element);

        $ANCHOR

        if (comparison < 0) {
            memcpy(result_element_ptr, second_element_ptr, sizeof(size_t));
            first_ind++;
        } else {
            memcpy(result_element_ptr, second_element_ptr, sizeof(size_t));
            second_ind++;
        }
    }

    while (first_ind < first_size) {
        ASSERT_FOR_ARR(first_ind,  first_size);
        ASSERT_FOR_ARR(first_ind + second_ind, result_arr);

        memcpy(MANUAL_IND((first_ind + second_ind) * sizeof(size_t), result_arr), MANUAL_IND(first_ind * sizeof(size_t), first_arr_copy), sizeof(size_t));
        first_ind++;
    }

    while (second_ind < second_size) {
        ASSERT_FOR_ARR(second_ind, second_size);
        ASSERT_FOR_ARR(first_ind + second_ind, result_arr);

        memcpy(MANUAL_IND((first_ind + second_ind) * sizeof(size_t), result_arr), MANUAL_IND(second_ind * sizeof(size_t), second_arr_copy), sizeof(size_t));
        second_ind++;
    }

    free(first_arr_copy);
    free(second_arr_copy);

    return SUCCESS;
}


int string_cmp(const void* const first_str, const void* const second_str) {
    assert( first_str != NULL);
    assert(second_str != NULL);

    return my_strncmp(((string*)first_str)->text, ((string*)second_str)->text, MIN(((string*)first_str)->text_sz, ((string*)second_str)->text_sz));
}


int int_cmp(const void* const first_element, const void* const second_element) {
    assert(first_element  != NULL);
    assert(second_element != NULL);

    return *(const int* const)first_element - *(const int* const)second_element;
}


error_code_e test_bubble_sort() {
    const size_t size1_x = 5;

    char str_array1[size1_x][MAX_STR_LEN] = {
        "BCDE",
        "ABCD",
        "HELLO",
        "a",
        "AAAA"
    };

    if ((LAST_ERROR_CODE = bubble_sort((char*)str_array1, size1_x, MAX_STR_LEN)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    // if ((LAST_ERROR_CODE = $print_str_matrix((char*)str_array1, size1_x, MAX_STR_LEN)) != SUCCESS) {
    //     PRINT_ERROR;
    //     return LAST_ERROR_CODE;
    // }

    printf("\n\n");

    const size_t size2_x = 11;

    char str_array2[size2_x][MAX_STR_LEN] = {
        "a",      // 1
        "\0\0\0", // 2
        "ZZZZZZ", // 3
        "8",      // 4
        "910",    // 5
        "1",      // 6
        "2",      // 7
        "6",      // 8
        "4",      // 9
        "3",      // 10
        ""
    };

    if ((LAST_ERROR_CODE = bubble_sort((char*)str_array2, size2_x, MAX_STR_LEN)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    // if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array2, size2_x, MAX_STR_LEN)) != SUCCESS) {
    //     PRINT_ERROR;
    //     return LAST_ERROR_CODE;
    // }

    return SUCCESS;
}


error_code_e test_selection_sort() {
    const size_t size_x = 5;

    char str_array[size_x][MAX_STR_LEN] = {
        "BCDE",
        "ABCD",
        "HELLO",
        "a",
        "AAAA"
    };

    if ((LAST_ERROR_CODE = selection_sort((char*)str_array, size_x, MAX_STR_LEN)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    // if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array, size_x, MAX_STR_LEN)) != SUCCESS) {
    //     PRINT_ERROR;
    //     return LAST_ERROR_CODE;
    // }

    return SUCCESS;
}


error_code_e test_merge_sort() {
    const size_t size = 11;

    const char* str1 = "a";
    const char* str2 = "\0\0\0";
    const char* str3 = "ZZZZZZ";
    const char* str4 = "8";
    const char* str5 = "910";
    const char* str6 = "1";
    const char* str7 = "2";
    const char* str8 = "6";
    const char* str9 = "4";
    const char* str10 = "3";
    const char* str11 = "";

    const char* str_array[size] = {
        str1,
        str2,
        str3,
        str4,
        str5,
        str6,
        str7,
        str8,
        str9,
        str10,
        str11
    };

    if ((LAST_ERROR_CODE = merge_sort((void*)str_array, size, string_cmp)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    // if ((LAST_ERROR_CODE = print_strptr_arr(str_array, size)) != SUCCESS) {
    //     PRINT_ERROR;
    //     return LAST_ERROR_CODE;
    // }

    return SUCCESS;
}


