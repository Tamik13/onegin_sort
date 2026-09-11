#include <stdio.h>
#include "debuging.h"

#define LEN(arr) sizeof(arr) / sizeof(arr[0])

size_t my_strlen    (const char* str);
error_code_e my_puts(const char* str);
char* my_strncpy    (char* dest,      const char* src, size_t count);
char* my_strncat    (char* dest,      const char* src, size_t count);
int   my_strncmp    (const char* lhs, const char* rhs, size_t count);
