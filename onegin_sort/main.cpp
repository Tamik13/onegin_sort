#include "string_sotr.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

struct string {
    long long text_sz = -1;
    char* text;
};

error_code_e read_file                (string* const buffer);
error_code_e replace_slash_n          (string* const buffer,       size_t* const count_replace);
error_code_e initialization_ptr_on_str(const string* const buffer, char** const ptr_on_str);

static error_code_e LAST_ERROR_CODE = INIT_VALUE;
const char* FILE_NAME = "clear_onegin.txt";

int main() {
    string buffer = {};
    size_t count_strings = 0;
    char** ptr_on_str = NULL;

    if ((LAST_ERROR_CODE = read_file(&buffer)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((LAST_ERROR_CODE = replace_slash_n(&buffer, &count_strings)) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((ptr_on_str = (char**)calloc(count_strings, sizeof(char**))) == NULL) {
        LAST_ERROR_CODE = ERROR_IN_MEM_ALLOCATION;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }



    return 0;
}

error_code_e read_file(string* const buffer) {
    assert(buffer != NULL);

    int file = open(FILE_NAME, O_RDONLY);
    struct stat buff = {};

    if (stat(FILE_NAME, &buff) == -1) {
        LAST_ERROR_CODE = STAT_READ_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((buffer->text = (char*)calloc((size_t)buff.st_size, sizeof(char))) == NULL) {
        LAST_ERROR_CODE = ERROR_IN_MEM_ALLOCATION;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if (file == -1) {
        LAST_ERROR_CODE = OPEN_FILE_ERROR;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if ((buffer->text_sz = read(file, buffer->text, (size_t)buff.st_size)) == -1) {
        LAST_ERROR_CODE = ERROR_DURING_READING;
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    if (close(file) == -1) {
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

error_code_e initialization_ptr_on_str(const string* const buffer, char** const ptr_on_str) {
    assert(buffer     != NULL);
    assert(ptr_on_str != NULL);

    for (size_t letter_ind = 0; letter_ind < buffer->text_sz; letter_ind++) {
        ASSERT_FOR_ARR(letter_ind, buffer->text_sz);

    }

    return SUCCESS;
}
