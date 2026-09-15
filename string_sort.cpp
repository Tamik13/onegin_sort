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

error_code_e merge_sort(void* array, const size_t size_x, const size_t left, const size_t right, comparator cmp) {
    assert(array != NULL);
    assert(right > left);

    COLOR_TEXT_START(VIOLET);
    $size_t(left,  " ");
    $size_t(right, "\n");
    COLOR_TEXT_END;
    print_intptr_arr((int**)((char*)array + left * sizeof(size_t)), right - left);
    // PRINT_STR_ARR((char**)((char*)str_array + left * sizeof(size_t)), right - left);

    if (right - left == 1) {
        return SUCCESS;
    }

    size_t middle = (left + right) / 2;

    merge_sort(array, size_x, left, middle, cmp);
    merge_sort(array, size_x, middle, right, cmp);

    void*  first_str_array_copy = calloc(middle - left,  sizeof(size_t));
    void* second_str_array_copy = calloc(right - middle, sizeof(size_t));

    memcpy(first_str_array_copy,  (void*)((size_t*)array + left),   sizeof(size_t) * (middle - left));
    memcpy(second_str_array_copy, (void*)((size_t*)array + middle), sizeof(size_t) * (right - middle));

    // $size_t(middle - left, " ");
    // $size_t(sizeof(first_str_array_copy), "\n");

    // PRINT_STR_ARR((char**)first_str_array_copy,  middle - left);
    // PRINT_STR_ARR((char**)second_str_array_copy, right - middle);

    merge(first_str_array_copy, middle - left, second_str_array_copy, right - middle, (size_t*)array + left, right - left, cmp);

    // PRINT_STR_ARR((char**)((char*)str_array + left * sizeof(size_t)),  right - left);

    free(first_str_array_copy);
    free(second_str_array_copy);

    return SUCCESS;
}


error_code_e merge(const void* const first_arr, size_t first_size, const void* const second_arr, size_t second_size, void* const result_arr, size_t result_size, comparator cmp) {
    assert(first_arr  != NULL);
    assert(second_arr != NULL);
    assert(first_size + second_size == result_size);

    size_t x = 0, y = 0;

    $size_t(first_size, " ");
    $size_t(second_size, " ");
    $size_t(result_size, "\n");

    print_intptr_arr((int**)result_arr, result_size);

    while (x < first_size && y < second_size) {
        ASSERT_FOR_ARR(x, first_size);
        ASSERT_FOR_ARR(y, second_size);
        ASSERT_FOR_ARR(x + y, result_size);

        $size_t(MANUAL_IND(x + y, sizeof(size_t), result_arr), " ");
        $size_t(MANUAL_IND(y, sizeof(size_t), second_arr), " ");
        $size_t(MANUAL_IND(x, sizeof(size_t), first_arr), "\n");

        int comparison = cmp((void*)MANUAL_IND(x, sizeof(size_t), first_arr), (void*)MANUAL_IND(y, sizeof(size_t), second_arr), MAX_STR_LEN);

        if (comparison >= 0) {
            memcpy((void*)MANUAL_IND((x + y), sizeof(size_t), result_arr), (void*)MANUAL_IND(x, sizeof(size_t), first_arr), sizeof(size_t));
            x++;
        } else {
            memcpy((void*)MANUAL_IND((x + y), sizeof(size_t), result_arr), (void*)MANUAL_IND(y, sizeof(size_t), second_arr), sizeof(size_t));
            y++;
        }
        $size_t(x, " "); $size_t(y, "\n");
    }

    while (x < first_size && x + y < result_size) {
        ASSERT_FOR_ARR(x, first_size);
        ASSERT_FOR_ARR(x + y, result_size);

        $size_t(MANUAL_IND((x + y), sizeof(size_t), result_arr), " ");
        $size_t(MANUAL_IND(x, sizeof(size_t), first_arr), "\n");

        memcpy((void*)MANUAL_IND((x + y), sizeof(size_t), result_arr), (void*)MANUAL_IND(x, sizeof(size_t), first_arr), sizeof(size_t));
        x++;

        $size_t(x, " "); $size_t(y, "\n");
    }

    while (y < second_size && x + y < result_size) {
        ASSERT_FOR_ARR(y, second_size);
        ASSERT_FOR_ARR(x + y, result_size);

        $size_t(MANUAL_IND((x + y), sizeof(size_t), result_arr), " ");
        $size_t(MANUAL_IND(y, sizeof(size_t), second_arr), "\n");

        memcpy((void*)MANUAL_IND((x + y), sizeof(size_t), result_arr), (void*)MANUAL_IND(y, sizeof(size_t), second_arr), sizeof(size_t));
        y++;

        $size_t(x, " "); $size_t(y, "\n");
    }

    // printf("%d\n", (*(int**)result_arr)[0]);
    print_intptr_arr((int**)result_arr, result_size);

    printf("URA\n");

    return SUCCESS;
}

error_code_e assignment(void* const lhs, void* const rhs, const size_t size, const size_t size_type) {
    assert(lhs != NULL);
    assert(rhs != NULL);

    size_t num_block = 0;

    switch (size_type) {
        case sizeof(uint64_t):
            ASSIGN_BLOCK(uint64_t);
            break;
        case sizeof(uint32_t):
            ASSIGN_BLOCK(uint32_t);
            break;
        case sizeof(uint16_t):
            ASSIGN_BLOCK(uint16_t);
            break;
        case sizeof(uint8_t):
            ASSIGN_BLOCK(uint8_t);
            break;
        default:
            return UNDEFINED_TYPE;
    }

    return SUCCESS;
}

int str_cmp(void* const first_element, void* const second_element, const size_t size) {
    assert(first_element  != NULL);
    assert(second_element != NULL);

    return strncmp((char*)first_element, (char*)second_element, size);
}

int int_cmp(void* const first_element, void* const second_element, const size_t size) {
    assert(first_element  != NULL);
    assert(second_element != NULL);

    return *(int*)first_element - *(int*)second_element;
}

// error_code_e test_bubble_sort() {
//     const size_t size1_x = 5;
//
//     char str_array1[size1_x][MAX_STR_LEN] = {
//         "BCDE",
//         "ABCD",
//         "HELLO",
//         "a",
//         "AAAA"
//     };
//
//     if ((LAST_ERROR_CODE = bubble_sort((char*)str_array1, size1_x, MAX_STR_LEN)) != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array1, size1_x, MAX_STR_LEN)) != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     printf("\n\n");
//
//     const size_t size2_x = 11;
//
//     char str_array2[size2_x][MAX_STR_LEN] = {
//         "a",      // 1
//         "\0\0\0", // 2
//         "ZZZZZZ", // 3
//         "8",      // 4
//         "910",    // 5
//         "1",      // 6
//         "2",      // 7
//         "6",      // 8
//         "4",      // 9
//         "3",      // 10
//         ""
//     };
//
//     if ((LAST_ERROR_CODE = bubble_sort((char*)str_array2, size2_x, MAX_STR_LEN)) != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array2, size2_x, MAX_STR_LEN)) != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     return SUCCESS;
// }


// error_code_e test_selection_sort() {
//     const size_t size_x = 5;
//
//     char str_array[size_x][MAX_STR_LEN] = {
//         "BCDE",
//         "ABCD",
//         "HELLO",
//         "a",
//         "AAAA"
//     };
//
//     if ((LAST_ERROR_CODE = selection_sort((char*)str_array, size_x, MAX_STR_LEN)) != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array, size_x, MAX_STR_LEN)) != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     return SUCCESS;
// }

error_code_e test_merge_sort() {
    const size_t size = 3;

    char* const str1 = "BCDE";
    char* const str2 = "ABCDE";
    char* const str3 = "Z";

    char* str_array[size] = {
        str1,
        str2,
        str3
    };

    int num1 = 4;
    int num2 = 7;
    int num3 = 6;

    int* int_array[size] = {
        &num1,
        &num2,
        &num3
    };

    if ((LAST_ERROR_CODE = merge_sort((void*)int_array, size, 0, size, int_cmp)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = print_intptr_arr(int_array, size)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    return SUCCESS;
}


