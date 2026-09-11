#define PRINT_ERROR               printf("%s:%d Error in %s\n",  __FILE__, __LINE__, __FUNCTION__);
#define ASSERT_FOR_ARR(ind, size) assert(0 <= (size_t)ind && (size_t)ind < (size_t)size);

#define $int(num, end)     printf(#num " = %d%s", num, end)
#define $double(num, end)  printf(#num " = %ld%s", num, end)
#define $llint(num, end)   printf(#num " = %lld%s", num, end)
#define $uint(num, end)    printf(#num " = %ud%s", num, end)
#define $char(symbol, end) printf(#symbol " = <%c>, %d%s", symbol, symbol, end)
#define $string(str, end)  printf(#str " = <%s>%s", str, end)
#define $size_t(num, end)  printf(#num " = %zu%s", num, end)
#define $pointer(ptr, end) printf(#ptr " = %p%s", ptr, end)

enum error_code_e {
    SUCCESS,
    ERROR_IN_INPUT_PARAM,
    INCORRECT_MATRIX_SIZE,
    FIND_EOF,
    INIT_VALUE
};

error_code_e get_random_int_arr();
