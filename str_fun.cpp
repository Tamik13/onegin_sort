#include "str_fun.h"

error_code_e test_my_str_functions() { // TODO БОЛЬШЕ ТЕСТОВ
    const char* str1 = "phisteh";
    const char* str2 = "URAAAAAAAAAAAAAAAA";

    // my_strlen

    printf("my_strlen: %d\n", my_strnlen(str1, MAX_STR_LEN) == strlen(str1));

    // my_puts

    my_puts("\nmy_puts:\n\n");

    puts(str1);

    my_puts(str1);
    putchar('\n');

    // my_strncpy

    char str3[50] = "phisteh";
    char str4[50] = "phisteh";

    my_puts("\nmy_strncpy:\n\n");

    my_strncpy(str3, str2, LEN(str3));
    my_puts(str3);

    putchar('\n');

    strncpy(str4, str2, LEN(str4));
    my_puts(str4);

    // my_strncat

    char str5[50] = "phisteh";
    char str6[50] = "phisteh";

    my_puts("\n\nmy_strncpy:\n\n");

    my_strncat(str5, str2, LEN(str5));
    my_puts(str5);

    putchar('\n');

    strncat(str6, str2, LEN(str6));
    my_puts(str6);

    // my_strcmp

    printf("\n\nmy_strcmp: %d\n", my_strncmp(str5, str6, MIN(LEN(str5), LEN(str6))) == strncmp(str5, str6, MIN(LEN(str5), LEN(str6))));

    return SUCCESS;
}


size_t my_strnlen(const char* str, size_t max_size) {
    assert(str != NULL);

    size_t size = 0;

    while (size < max_size && *str++ != '\0') {
        size++;
    }

    return size;
}


error_code_e my_puts(const char* str) {
    if (str == NULL) {
        return ERROR_IN_INPUT_PARAM;
    }

    while (*str != '\0') {
        putchar(*str++);
    }

    return SUCCESS;
}


char* my_strncpy(char* dest, const char* src, size_t count) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    while (count-- && *src != '\0') {
        *dest = *src;

        dest++; src++;
    }

    return dest;
}


char* my_strncat(char* dest, const char* src, size_t count) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    while (*dest != '\0') {
        dest++;
    }

    while (count-- && *src != '\0') {
        *dest = *src;

        dest++; src++;
    }

    return dest;
}


int my_strncmp(const char* lhs, const char* rhs, size_t count) {
    if (lhs == NULL || rhs == NULL) return NULL;
    if (count == 0) return 0;

    count--;

    while (count && *lhs != '\0' && *rhs != '\0') {
        if (*rhs != *lhs) return *lhs - *rhs;

        count--; lhs++; rhs++;
    }

    return *lhs - *rhs;
}


error_code_e print_const_memory() {
    // const char* str = "phisteh";
    const char* str2 = "URAAAAAAAAAAAAAAAA";

    for (int i = 0; i < 1000; i++) {
        putchar(str2[i]);
    }

    return SUCCESS;
}
