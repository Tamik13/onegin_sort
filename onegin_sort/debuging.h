#include <stdio.h>
#include <assert.h>
#include <errno.h>

#define PRINT_ERROR    \
    fprintf(stderr, "%s:%d " COLOR_TEXT("ERROR CODE: ", RED) "%d   " COLOR_TEXT("ERRNO: ", RED) "%s  %s\n",  __FILE__, __LINE__, LAST_ERROR_CODE, strerror(errno), __FUNCTION__);

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
    fprintf(stderr, "\n");

#define $PRINT_PTR_ARR(arr, size)                                                                   \
    assert(arr != NULL);                                                                            \
    $ANCHOR                                                                                         \
                                                                                                    \
    for (size_t x = 0; x < size; x++) {                                                             \
        ASSERT_FOR_ARR(x, size);                                                                    \
        fprintf(stderr, COLOR_TEXT(#arr, VIOLET) "[%zu] = %p\n", x, ((void**)arr)[x]);              \
    }                                                                                               \
                                                                                                    \
    printf("\n");

#define $PRINT_INTPTR_ARR(int_arr, size)                                                            \
    assert(int_arr != NULL);                                                                        \
    $ANCHOR                                                                                         \
                                                                                                    \
    for (size_t x = 0; x < size; x++) {                                                             \
        ASSERT_FOR_ARR(x, size);                                                                    \
                                                                                                    \
        fprintf(stderr, COLOR_TEXT(#int_arr, VIOLET) "[%zu] = %d\n", x, *((int**)int_arr)[x]);      \
    }                                                                                               \
                                                                                                    \
    fprintf(stderr, "\n");

#define $DEBUG_QSORT(reason) $debug_qsort((int*)array, size, left, right, middle_el, type_size, reason);


#define RED    "91"
#define GREEN  "92"
#define BLUE   "94"
#define YELLOW "33"
#define VIOLET "35"

#define COLOR_TEXT(STR, COLOR)  "\033[" COLOR "m" STR "\033[0m"
#define COLOR_TEXT_START(COLOR) "\033[" COLOR "m"
#define COLOR_TEXT_END          "\033[0m"

#define $int(num)     $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET)    " = %d\n\n",       num)
#define $double(num)  $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET)    " = %ld\n\n",      num)
#define $llint(num)   $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET)    " = %lld\n\n",     num)
#define $uint(num)    $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET)    " = %ud\n\n",      num)
#define $char(symbol) $ANCHOR fprintf(stderr, COLOR_TEXT(#symbol, VIOLET) " = <%c>, %d\n\n", symbol, symbol)
#define $string(str)  $ANCHOR fprintf(stderr, COLOR_TEXT(#str, VIOLET)    " = <%s>\n\n",     str)
#define $size_t(num)  $ANCHOR fprintf(stderr, COLOR_TEXT(#num, VIOLET)    " = %zu\n\n",      num)
#define $ptr(ptr)     $ANCHOR fprintf(stderr, COLOR_TEXT(#ptr, VIOLET)    " = %p\n\n",       ptr)

enum error_code_e {
    SUCCESS                  = 0,
    ERROR_IN_INPUT_PARAM     = 1,
    INCORRECT_MATRIX_SIZE    = 2,
    FIND_EOF                 = 3,
    UNDEFINED_TYPE           = 4,
    OPEN_FILE_ERROR          = 5,
    CLOSE_FILE_ERROR         = 6,
    STAT_READ_ERROR          = 7,
    ERROR_DURING_READING     = 8,
    ERROR_IN_MEM_ALLOCATION  = 9,
    ERROR_DURING_WRITING     = 10,
    INCORRECT_ARGC           = 11,
    INIT_VALUE               = -1
};

void $debug_qsort     (const int* array,             const size_t size,   const size_t left,      const size_t right,     void* middle_el,           const char* const reason);
void $print_arr       (const void* const arr,        const size_t size,   const size_t size_type, const char* const type, const char* const message);
void $print_strptr_arr(const char* const arr[],      const size_t size);
void $print_str_matrix(const char* const arr,        const size_t size_x, const size_t size_y);
void $print_int_arr   (const int int_array[],        const size_t size);
void $print_intptr_arr(const int* const int_array[], const size_t size);
