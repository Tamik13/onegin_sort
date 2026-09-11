#include "string_sotr.h"

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

error_code_e merge_sort(char* str_array, const size_t size_x, const size_t left,  const size_t right) {
    assert(str_array != NULL);

    size_t middle = (left + right) / 2;

    merge_sort(str_array, size_x, left, middle);
    merge_sort(str_array, size_x, middle, right);

    char*  first_str_array_copy = (char*)calloc(middle - left,  sizeof(size_t));
    char* second_str_array_copy = (char*)calloc(right - middle, sizeof(size_t));

    merge(first_str_array_copy, middle - left, second_str_array_copy, right - middle, str_array + left, right - left);

    free(first_str_array_copy);
    free(second_str_array_copy);

    return SUCCESS;
}


error_code_e print_str_matrix(const char* const str_array, const size_t size_x, const size_t size_y) {
    assert(str_array != NULL);

    for (size_t x = 0; x < size_x; x++) {
        printf("<%s>\n", &str_array[x * size_y]);
    }

    return SUCCESS;
}


error_code_e merge(char* first_arr, size_t first_size, char* second_arr, size_t second_size, char* result_arr, size_t result_size) {
    assert(first_arr  != NULL);
    assert(second_arr != NULL);

    size_t x = 0, y = 0;

    while (x < first_size && y < second_size) {
        ASSERT_FOR_ARR(x, first_size);
        ASSERT_FOR_ARR(y, second_size);
        ASSERT_FOR_ARR(x + y, result_size);

        int comparison = my_strncmp(&first_arr[x], &second_arr[y], MAX_STR_LEN);

        if (comparison <= 0) {
            result_arr[x + y] = first_arr[x];
            x++;
        } else if (comparison > 0) {
            result_arr[x + y] = second_arr[y];
            y++;
        }
    }

    while (x < first_size) {
        ASSERT_FOR_ARR(x, first_size);
        result_arr[x + y] = first_arr[x];
        x++;
    }

    while (y < second_size) {
        ASSERT_FOR_ARR(y, second_size);
        result_arr[x + y] = second_arr[y];
        x++;
    }

    return SUCCESS;
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

    if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array1, size1_x, MAX_STR_LEN)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

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

    if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array2, size2_x, MAX_STR_LEN)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

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

    if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array, size_x, MAX_STR_LEN)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    return SUCCESS;
}

error_code_e test_merge_sort() {
    const size_t size1_x = 3;

    const char* const str1 = "BCDE";
    const char* const str2 = "ABCDE";
    const char* const str3 = "Z";

    const char* str_array1[size1_x] = {
        str1,
        str2,
        str3
    };

    if ((LAST_ERROR_CODE = merge_sort((char*)str_array1, size1_x, 0, size1_x)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = print_str_matrix((char*)str_array1, size1_x, MAX_STR_LEN)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    return SUCCESS;
}


