#include "string_sotr.h"

const size_t MAX_STR_LEN = 100;

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

    size_t ind = 0;
    uint64_t buffer = 0;

    while (size - ind >= sizeof(uint64_t)) {
        ASSERT_FOR_ARR(ind, size);
        buffer = *(uint64_t*)(first_str + ind);
        *(uint64_t*)(first_str + ind) = *(uint64_t*)(second_str + ind);
        *(uint64_t*)(second_str + ind) = buffer;
        ind += sizeof(uint64_t);
    }

    while (size - ind >= sizeof(uint32_t)) {
        ASSERT_FOR_ARR(ind, size);
        buffer = *(uint32_t*)(first_str + ind);
        *(uint32_t*)(first_str + ind) = *(uint32_t*)(second_str + ind);
        *(uint32_t*)(second_str + ind) = (uint32_t)buffer;
        ind += sizeof(int);
    }

    while (size - ind >= sizeof(uint16_t)) {
        ASSERT_FOR_ARR(ind, size);
        buffer = *(uint16_t*)(first_str + ind);
        *(uint16_t*)(first_str + ind) = *(uint16_t*)(second_str + ind);
        *(uint16_t*)(second_str + ind) = (uint16_t)buffer;
        ind += sizeof(short);
    }

    while (size - ind >= sizeof(char)) {
        ASSERT_FOR_ARR(ind, size);
        buffer = *(char*)(first_str + ind);
        *(char*)(first_str + ind) = *(char*)(second_str + ind);
        *(char*)(second_str + ind) = (char)buffer;
        ind += sizeof(char);
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

error_code_e merge_sort(void* const array, const size_t size, comparator cmp) {
    assert(array != NULL);

    $START_FUNCTION

    if (size <= 1) {
        return SUCCESS;
    }

    // $PRINT_PTR_ARR(array, size);
    $ptr(array);


    size_t middle = size / 2;

    void* left_array  = (void**)array;
    void* right_array = (void**)array + middle;

    $ptr(left_array);
    $ptr(right_array);

    const size_t left_size  = middle;
    const size_t right_size = size - middle;

    $size_t(middle);
    $size_t(size - middle);

    merge_sort(left_array,  left_size,  cmp);
    merge_sort(right_array, right_size,  cmp);

    merge(left_array, left_size, right_array, right_size, array, size, cmp);

    $PRINT_INTPTR_ARR(array, size);

    $END_FUNCTION;

    return SUCCESS;
}


error_code_e merge(const void* const first_arr, const size_t first_size, const void* const second_arr, const size_t second_size, void* const result_arr, const size_t result_size, comparator cmp) {
    assert(first_arr  != NULL);
    assert(second_arr != NULL);
    assert(first_size + second_size == result_size);

    $START_FUNCTION


    // PRINT_PTR_ARR(first_arr, first_size);
    // PRINT_PTR_ARR(second_arr, second_size);
    // PRINT_PTR_ARR(result_arr, result_size);



    void* const first_arr_copy  = calloc(first_size,  sizeof(size_t));
    void* const second_arr_copy = calloc(second_size, sizeof(size_t));

    memcpy(first_arr_copy,  first_arr,  first_size  * sizeof(size_t));
    memcpy(second_arr_copy, second_arr, second_size * sizeof(size_t));

    $PRINT_INTPTR_ARR(first_arr_copy, first_size);
    $PRINT_INTPTR_ARR(second_arr_copy, second_size);



    // PRINT_PTR_ARR(first_arr_copy, first_size);
    // PRINT_PTR_ARR(second_arr_copy, second_size);

    size_t first_ind = 0, second_ind = 0;

    while (first_ind < first_size && second_ind < second_size) {
        ASSERT_FOR_ARR(first_ind,  first_size);
        ASSERT_FOR_ARR(second_ind, second_size);
        ASSERT_FOR_ARR(first_ind + second_ind, result_arr);



        int comparison = cmp((const void* const)*((const size_t* const)first_arr_copy + first_ind), (const void* const)*((const size_t* const)second_arr_copy + second_ind), sizeof(size_t));

        $int(comparison);
        $int(*(int*)*((const size_t* const)first_arr_copy  +  first_ind));
        $int(*(int*)*((const size_t* const)second_arr_copy + second_ind));

        if (comparison < 0) {
            memcpy(MANUAL_IND((first_ind + second_ind) * sizeof(size_t), result_arr), MANUAL_IND(first_ind * sizeof(size_t), first_arr_copy), sizeof(size_t));
            first_ind++;
        } else {
            memcpy(MANUAL_IND((first_ind + second_ind) * sizeof(size_t), result_arr), MANUAL_IND(second_ind * sizeof(size_t), second_arr_copy), sizeof(size_t));
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


    $PRINT_INTPTR_ARR(result_arr, result_size);
    $PRINT_INTPTR_ARR(first_arr_copy, first_size);
    $PRINT_INTPTR_ARR(second_arr_copy, second_size);

    // PRINT_PTR_ARR(first_arr_copy, first_size);
    // PRINT_PTR_ARR(second_arr_copy, second_size);
    // PRINT_PTR_ARR(result_arr, result_size);



    free(first_arr_copy);
    free(second_arr_copy);

    $END_FUNCTION

    return SUCCESS;
}


int str_cmp(const void* const first_element, const void* const second_element, const size_t size) {
    assert(first_element  != NULL);
    assert(second_element != NULL);

    return strncmp((const char* const)first_element, (const char* const)second_element, size);
}

int int_cmp(const void* const first_element, const void* const second_element, const size_t size) {
    assert(first_element  != NULL);
    assert(second_element != NULL);

    return *(const int* const)first_element - *(const int* const)second_element;
}


error_code_e test_merge_sort() {
    const size_t size = 3;

    // char* const str1 = "BCDE";
    // char* const str2 = "ABCDE";
    // char* const str3 = "Z";

    // char* str_array[size] = {
    //     str1,
    //     str2,
    //     str3
    // };

    int num1 = 4;
    int num2 = 7;
    int num3 = 6;

    int* int_array[size] = {
        &num1,
        &num2,
        &num3
    };



    $PRINT_PTR_ARR(int_array, size);

    if ((LAST_ERROR_CODE = merge_sort((void*)int_array, size, int_cmp)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    ;

    if ((LAST_ERROR_CODE = print_intptr_arr(int_array, size)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }



    return SUCCESS;
}


