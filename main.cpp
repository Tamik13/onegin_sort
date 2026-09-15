#include "string_sotr.h"

int main() {

    if ((LAST_ERROR_CODE = test_merge_sort()) != SUCCESS) {
        PRINT_ERROR;
        return LAST_ERROR_CODE;
    }

    my_puts("\n");

    // if ((LAST_ERROR_CODE = test_selection_sort()) != SUCCESS) {
    //     PRINT_ERROR;
    //     return LAST_ERROR_CODE;
    // }

    return 0;
}
