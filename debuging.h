#include <stdio.h>
#include <assert.h>

#define PRINT_ERROR               printf("%s:%d Error in %s\n",  __FILE__, __LINE__, __FUNCTION__);
#define ASSERT_FOR_ARR(ind, size) assert(0 <= (size_t)ind && (size_t)ind < (size_t)size);

#define $ANCHOR         fprintf(stderr, "%s:%d " COLOR_TEXT("ANCHOR",         VIOLET) " %s\n", __FILE__, __LINE__, __FUNCTION__);
#define $START_FUNCTION fprintf(stderr, "%s:%d " COLOR_TEXT("START FUNCTION", BLUE)   " %s\n", __FILE__, __LINE__, __FUNCTION__);
#define $END_FUNCTION   fprintf(stderr, "%s:%d " COLOR_TEXT("END FUNCTION",   YELLOW) " %s\n", __FILE__, __LINE__, __FUNCTION__);

#define $PRINT_STR_ARR(arr, size)                                                                   \
    assert(arr != NULL);                                                                            \
    $ANCHOR                                                                                         \
                                                                                                    \
    printf(COLOR_TEXT("%s:%d " #arr " %s", VIOLET) "\n", __FILE__,  __LINE__, __FUNCTION__);        \
    print_str_matrix(arr, size);                                                                    \
    getchar();                                                                                      \
                                                                                                    \
    printf("\n");

#define $PRINT_PTR_ARR(arr, size)               \
    assert(arr != NULL);                        \
    $ANCHOR                                     \
                                                \
    for (size_t x = 0; x < size; x++) {         \
        ASSERT_FOR_ARR(x, size);                \
        fprintf(stderr, COLOR_TEXT(#arr, VIOLET) "[%zu] = %p\n", x, ((void**)arr)[x]);           \
    }                                           \
                                                \
    printf("\n");

#define $PRINT_INTPTR_ARR(int_arr, size)                            \
    assert(int_arr != NULL);                                        \
    $ANCHOR                                                         \
                                                                    \
    for (size_t x = 0; x < size; x++) {                             \
        ASSERT_FOR_ARR(x, size);                                    \
                                                                    \
        fprintf(stderr, COLOR_TEXT(#int_arr, VIOLET) "[%zu] = %d\n", x, *((int**)int_arr)[x]);   \
    }                                                               \
                                                                    \
    printf("\n");

#define COLOR_TEXT(STR, COLOR)  "\033[" COLOR "m" STR "\033[0m"
#define COLOR_TEXT_START(COLOR) "\033[" COLOR "m"
#define COLOR_TEXT_END          "\033[0m"

#define RED    "91"
#define GREEN  "92"
#define BLUE   "94"
#define YELLOW "33"
#define VIOLET "35"

#define $int(num)     $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET) " = %d\n\n", num)
#define $double(num)  $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET) " = %ld\n\n", num)
#define $llint(num)   $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET) " = %lld\n\n", num)
#define $uint(num)    $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET) " = %ud\n\n", num)
#define $char(symbol) $ANCHOR fprintf(stderr, COLOR_TEXT(#symbol, VIOLET) " = <%c>, %d\n\n", symbol, symbol)
#define $string(str)  $ANCHOR fprintf(stderr, COLOR_TEXT(#str, VIOLET) " = <%s>\n\n", str)
#define $size_t(num)  $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET) " = %zu\n\n", num)
#define $ptr(ptr)     $ANCHOR fprintf(stderr, COLOR_TEXT(#ptr, VIOLET) " = %p\n\n", ptr)

enum error_code_e {
    SUCCESS,
    ERROR_IN_INPUT_PARAM,
    INCORRECT_MATRIX_SIZE,
    FIND_EOF,
    UNDEFINED_TYPE,
    INIT_VALUE
};

error_code_e print_arr       (const void* const arr,        const size_t size, const size_t size_type, const char* const type, const char* const message);
error_code_e print_str_matrix(const char* const arr[],      const size_t size);
error_code_e print_int_matrix(const int int_array[],        const size_t size_x, const size_t size_y);
error_code_e print_intptr_arr(const int* const int_array[], const size_t size);
