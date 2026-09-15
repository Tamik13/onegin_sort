#include <stdio.h>
#include <assert.h>

#define PRINT_ERROR               printf("%s:%d Error in %s\n",  __FILE__, __LINE__, __FUNCTION__);
#define ASSERT_FOR_ARR(ind, size) assert(0 <= (size_t)ind && (size_t)ind < (size_t)size);

#define PRINT_ARR(arr, size, size_type, type, message)                                           \
    printf(COLOR_TEXT("%s:%d " #arr " %s", VIOLET) "\n", __FILE__,  __LINE__, __FUNCTION__);     \               \
    print_arr(arr, size, size_type, type, message);                                              \
    getchar();                                                                                   \
    printf("\n");

#define PRINT_STR_ARR(arr, size)                                                                  \
    printf(COLOR_TEXT("%s:%d " #arr " %s", VIOLET) "\n", __FILE__,  __LINE__, __FUNCTION__);      \
    print_str_matrix(arr, size);                                                                  \
    getchar();                                                                                    \
    printf("\n");

#define COLOR_TEXT(STR, COLOR)  "\033[" COLOR "m" STR "\033[0m"
#define COLOR_TEXT_START(COLOR) "\033[" COLOR "m"
#define COLOR_TEXT_END          "\033[0m"

#define RED    "91"
#define GREEN  "92"
#define BLUE   "94"
#define YELLOW "33"
#define VIOLET "35"

#define $int(num, end)     printf(#num " = %d%s", num, end)
#define $double(num, end)  printf(#num " = %ld%s", num, end)
#define $llint(num, end)   printf(#num " = %lld%s", num, end)
#define $uint(num, end)    printf(#num " = %ud%s", num, end)
#define $char(symbol, end) printf(#symbol " = <%c>, %d%s", symbol, symbol, end)
#define $string(str, end)  printf(#str " = <%s>%s", str, end)
#define $size_t(num, end)  printf(#num " = %zu%s", num, end)
#define $ptr(ptr, end) printf(#ptr " = %p%s", ptr, end)

enum error_code_e {
    SUCCESS,
    ERROR_IN_INPUT_PARAM,
    INCORRECT_MATRIX_SIZE,
    FIND_EOF,
    UNDEFINED_TYPE,
    INIT_VALUE
};

error_code_e print_arr       (void* const arr,        const size_t size, const size_t size_type, const char* const type, const char* const message);
error_code_e print_str_matrix(char* const arr[],      const size_t size);
error_code_e print_int_arr   (const int  int_array[], const size_t size);
error_code_e print_int_matrix(const int  int_array[], const size_t size_x, const size_t size_y);
error_code_e print_intptr_arr(int* int_array[],       const size_t size);
