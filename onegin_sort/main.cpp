#include "string_sotr.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>



error_code_e read_file                (string* const buffer);
error_code_e replace_slash_n          (string* const buffer,           size_t* const count_replace);
error_code_e initialization_ptr_on_str(const string* const buffer,     string* const ptr_on_str);
error_code_e writing_in_file          (const string* const ptr_on_str, const size_t count_strings);



static error_code_e LAST_ERROR_CODE = INIT_VALUE;

const char*  INPUT_FILE_NAME =  "clear_onegin.txt";
const char* OUTPUT_FILE_NAME = "sorted_onegin.txt";

int main() {
//     string buffer = {};
//     size_t count_strings = 0;
//     string* ptr_on_str = NULL;
//
//     if ((LAST_ERROR_CODE = read_file(&buffer))                                != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     if ((LAST_ERROR_CODE = replace_slash_n(&buffer, &count_strings))          != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     if ((ptr_on_str      = (string*)calloc(count_strings, sizeof(char**)))    == NULL) {
//         LAST_ERROR_CODE = ERROR_IN_MEM_ALLOCATION;
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     if ((LAST_ERROR_CODE = initialization_ptr_on_str(&buffer, ptr_on_str))    != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     // if ((LAST_ERROR_CODE = merge_sort(ptr_on_str, count_strings, string_cmp)) != SUCCESS) {
//     //     PRINT_ERROR;
//     //     return LAST_ERROR_CODE;
//     // }
//
//     if ((LAST_ERROR_CODE = writing_in_file(ptr_on_str, count_strings))        != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
    const size_t size = 10;
    int array[size] = {1, 4, 10, 3, 7, 6, 2, 8, 9, 5};

    q_sort(array, size);

    return 0;
}

error_code_e read_file(string* const buffer) {
    assert(buffer != NULL);

    int input_file = open(INPUT_FILE_NAME, O_RDONLY);
    struct stat buff = {};

    if (stat(INPUT_FILE_NAME, &buff) == -1) {
        LAST_ERROR_CODE = STAT_READ_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((buffer->text = (char*)calloc((size_t)buff.st_size, sizeof(char))) == NULL) {
        LAST_ERROR_CODE = ERROR_IN_MEM_ALLOCATION;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if (input_file == -1) {
        LAST_ERROR_CODE = OPEN_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((buffer->text_sz = (size_t)read(input_file, buffer->text, (size_t)buff.st_size)) == (size_t)-1) {
        LAST_ERROR_CODE = ERROR_DURING_READING;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if (close(input_file) == -1) {
        LAST_ERROR_CODE = CLOSE_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    return SUCCESS;
}

error_code_e replace_slash_n(string* const buffer, size_t* const count_replace) {
    assert(buffer != NULL);

    for (size_t letter_ind = 0; letter_ind < buffer->text_sz; letter_ind++) {
        ASSERT_FOR_ARR(letter_ind, buffer->text_sz);
        if (buffer->text[letter_ind] == '\n') {
            buffer->text[letter_ind] = '\0';
            (*count_replace)++;
        }
    }

    return SUCCESS;
}

error_code_e initialization_ptr_on_str(const string* const buffer, string* ptr_on_str) {
    assert(buffer     != NULL);
    assert(ptr_on_str != NULL);

    size_t number_ptr = 0;
    size_t size_str = 0;

    ptr_on_str[number_ptr++].text = &buffer->text[0];

    for (size_t letter_ind = 1; letter_ind < (size_t)buffer->text_sz; letter_ind++) {
        ASSERT_FOR_ARR(letter_ind - 1, buffer->text_sz);

        if (buffer->text[letter_ind - 1] == '\0') {
            ASSERT_FOR_ARR(letter_ind, buffer->text_sz);

            ptr_on_str[number_ptr].text    = &buffer->text[letter_ind];
            ptr_on_str[number_ptr - 1].text_sz = size_str;

            size_str = 0; number_ptr++;
        }

        size_str++;
    }

    ptr_on_str[number_ptr - 1].text_sz = size_str;

    return SUCCESS;
}

error_code_e writing_in_file(const string* const ptr_on_str, const size_t count_strings) {
    assert(ptr_on_str != NULL);

    int output_file = open(OUTPUT_FILE_NAME, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);

    if (output_file == -1) {
        LAST_ERROR_CODE = OPEN_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    for (size_t string_ind = 0; string_ind < count_strings; string_ind++) {
        ASSERT_FOR_ARR(string_ind, count_strings);

        ptr_on_str[string_ind].text[ptr_on_str[string_ind].text_sz - 1] = '\n';

        if (write(output_file, ptr_on_str[string_ind].text, ptr_on_str[string_ind].text_sz) == -1) {
            LAST_ERROR_CODE = ERROR_DURING_WRITING;
            PRINT_ERROR;
            return LAST_ERROR_CODE;
        }

        printf("%s", ptr_on_str[string_ind].text);
    }

    return SUCCESS;
}


