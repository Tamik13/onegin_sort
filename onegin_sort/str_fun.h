#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "debuging.h"

#define MIN(x, y)   ((x < y) ? x : y)
#define LEN(arr)    sizeof(arr) / sizeof(arr[0]) // Писать только в функции где массив инициализируется
#define TO_STR(str) #str

error_code_e test_my_str_functions();

struct string {
    size_t text_sz = 0;
    char* text;
};

size_t my_strnlen   (const char* str, size_t max_size);
error_code_e my_puts(const char* str);
char* my_strncpy    (char* dest,      const char* src, size_t count);
char* my_strncat    (char* dest,      const char* src, size_t count);
int   my_strncmp    (const char* lhs, const char* rhs, size_t count);

error_code_e print_const_memory();
