#include "string_sotr.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

#define STAT_GET_SIZE(file_size) \
    struct stat buff = {};                      \
                                                \
    if (stat(input_file_name, &buff) == -1) {   \
        LAST_ERROR_CODE = STAT_READ_ERROR;      \
        PRINT_ERROR;                            \
        return LAST_ERROR_CODE;                 \
    }                                           \
                                                \
    file_size = (size_t)buff.st_size;

error_code_e command_line_processing  (const int argc,                 const char*const*const argv,       const char** const input_file_name,      const char** const output_file_name);
error_code_e read_file                (string* const buffer,           const char* const input_file_name);
error_code_e count_slash_n            (string* const buffer,           size_t* const count_replace);
error_code_e initialization_ptr_on_str(const string* const buffer,     string* const ptr_on_str);
error_code_e clear_file               (const char*   const file_name);
error_code_e writing_in_file          (const string* const ptr_on_str, const size_t count_strings,        const char* const output_file_name);

int first_string_cmp (const void* const first_element, const void* const second_element);
int second_string_cmp(const void* const first_element, const void* const second_element);

static error_code_e LAST_ERROR_CODE = INIT_VALUE;

int main(const int argc, const char*const*const argv) {
    const char*  input_file_name = NULL;
    const char* output_file_name = NULL;
    string buffer = {};
    size_t count_strings = 0;
    string* ptr_on_str = NULL;

//     if ((LAST_ERROR_CODE = test_q_sort()) != SUCCESS) {
//         PRINT_ERROR;
//         return LAST_ERROR_CODE;
//     }
//
//     return SUCCESS;

    if ((LAST_ERROR_CODE = command_line_processing(argc, argv, &input_file_name, &output_file_name))) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    // $string(input_file_name);
    // $string(output_file_name);

    if ((LAST_ERROR_CODE = read_file(&buffer, input_file_name))                          != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = count_slash_n(&buffer, &count_strings))                       != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((ptr_on_str      = (string*)calloc(count_strings, sizeof(char**)))               == NULL) {
        LAST_ERROR_CODE = ERROR_IN_MEM_ALLOCATION;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = initialization_ptr_on_str(&buffer, ptr_on_str))               != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = q_sort(ptr_on_str,            count_strings,
                                  sizeof(ptr_on_str[0]), first_string_cmp))              != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = clear_file(output_file_name))                                 != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = writing_in_file(ptr_on_str, count_strings, output_file_name)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    qsort(ptr_on_str, count_strings, sizeof(ptr_on_str[0]), second_string_cmp);

    if ((LAST_ERROR_CODE = writing_in_file(ptr_on_str, count_strings, output_file_name)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = writing_in_file(&buffer, 1, output_file_name))                != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    printf(COLOR_TEXT("SUCCESS\n", GREEN));

    return 0;
}

error_code_e command_line_processing(const int argc, const char*const*const argv, const char** const input_file_name, const char** const output_file_name) {
    assert(argv != NULL);

    if (argc == 1) {
        *input_file_name  = "clear_onegin.txt";  // TODO: разобраться с const
        *output_file_name = "sorted_onegin.txt";
        return SUCCESS;

    } else if (argc != 3) {
        LAST_ERROR_CODE = INCORRECT_ARGC;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    *input_file_name  = argv[1];
    *output_file_name = argv[2];

    return SUCCESS;
}

error_code_e read_file(string* const buffer, const char* const input_file_name) {
    assert(buffer != NULL);

    int input_file = open(input_file_name, O_RDONLY);
    size_t size_input_file;

    STAT_GET_SIZE(size_input_file); // TODO Define stat

    if ((buffer->text = (char*)calloc(size_input_file, sizeof(char))) == NULL) {
        LAST_ERROR_CODE = ERROR_IN_MEM_ALLOCATION;
        PRINT_ERROR; // TODO: strerror
        return LAST_ERROR_CODE;
    }

    if (input_file == -1) {
        LAST_ERROR_CODE = OPEN_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((buffer->text_sz = (size_t)read(input_file, buffer->text, (size_t)buff.st_size) + 1) == (size_t)-1) {
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

error_code_e count_slash_n(string* const buffer, size_t* const count_str) {
    assert(buffer != NULL);

    for (size_t letter_ind = 0; letter_ind < buffer->text_sz; letter_ind++) {
        ASSERT_FOR_ARR(letter_ind, buffer->text_sz);
        if (buffer->text[letter_ind] == '\n') { // TODO: \0 поправить
            (*count_str)++;
        }
    }

    return SUCCESS;
}

error_code_e initialization_ptr_on_str(const string* const buffer, string* ptr_on_str) {
    assert(buffer     != NULL);
    assert(ptr_on_str != NULL);

    size_t number_ptr = 0;
    size_t size_str = 0;

    if (buffer->text_sz == 0) {
        return SUCCESS;
    }

    ptr_on_str[number_ptr++].text = &buffer->text[0];

    for (size_t letter_ind = 1; letter_ind < (size_t)buffer->text_sz; letter_ind++) {
        ASSERT_FOR_ARR(letter_ind - 1, buffer->text_sz);

        if (buffer->text[letter_ind - 1] == '\n') {
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

error_code_e clear_file(const char* const FILE_NAME) {

    int output_file = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IWRITE);

    if (output_file == -1) {
        LAST_ERROR_CODE = OPEN_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if (close(output_file) == -1) {
        LAST_ERROR_CODE = CLOSE_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    return SUCCESS;
}

error_code_e writing_in_file(const string* const ptr_on_str, const size_t count_strings, const char* const output_file_name) {
    assert(ptr_on_str != NULL);

    int output_file = open(output_file_name, O_WRONLY | O_CREAT |  O_APPEND, S_IWRITE);

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
    }

    if (close(output_file) == -1) {
        LAST_ERROR_CODE = CLOSE_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    return SUCCESS;
}

int first_string_cmp(const void* const first_element, const void* const second_element) {
    assert(first_element  != NULL);
    assert(second_element != NULL);

    // $ANCHOR

    const string* const first_str  = (const string* const)first_element;
    const string* const second_str = (const string* const)second_element;

//     $size_t(first_str->text_sz);
//     $ptr(second_str);
//
//     $ANCHOR

    size_t  first_ind = 0;
    size_t second_ind = 0;

    while (first_ind <  first_str->text_sz &&  first_str->text[first_ind]  != '\n' &&
          second_ind < second_str->text_sz && second_str->text[second_ind] != '\n') {

        // $ANCHOR

        while (first_ind < first_str->text_sz && !isalpha(first_str->text[first_ind]))     first_ind++;
        while (second_ind < second_str->text_sz && !isalpha(second_str->text[second_ind])) second_ind++;

        if(second_ind >= second_str->text_sz || first_ind >= first_str->text_sz) return 0;

        if (first_str->text[first_ind] - second_str->text[second_ind] != 0) {
            return first_str->text[first_ind] - second_str->text[second_ind];
        }

        first_ind++; second_ind++;
    }

    return first_str->text[first_ind] - second_str->text[second_ind];
}

int second_string_cmp(const void* first_element, const void* second_element) {
    assert(first_element  != NULL);
    assert(second_element != NULL);

    const string* const first_str  = (const string* const)first_element;
    const string* const second_str = (const string* const)second_element;

    long long  first_ind = (long long)(first_str->text_sz  - 1);
    long long second_ind = (long long)(second_str->text_sz - 1);

    while (first_ind >= 0 && first_str->text[first_ind]   != '\n' &&
          second_ind >= 0 && second_str->text[second_ind] != '\n') {

        // $ANCHOR

        while (first_ind  >= 0 && !isalpha( first_str->text[first_ind]))  first_ind--;
        // $ANCHOR
        while (second_ind >= 0 && !isalpha(second_str->text[second_ind])) second_ind--;

        // $ANCHOR

        if(second_ind < 0 || first_ind < 0) return first_str->text[first_ind] - second_str->text[second_ind];

        // $ANCHOR

        if (first_str->text[first_ind] - second_str->text[second_ind] != 0) {
            return first_str->text[first_ind] - second_str->text[second_ind];
        }

        // $ANCHOR

        first_ind--; second_ind--;
    }

    // $ANCHOR

    return first_str->text[first_ind] - second_str->text[second_ind];
}
