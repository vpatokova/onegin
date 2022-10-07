#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "sort.h"
#include "ERROR_CODES.h"

int main(void)
{
    const char *input_file_path  = "test.txt";
    const char *output_file_path = "out.txt";
    char ***arr_ptr_adr = 0;
    
    if (read_file(input_file_path, &arr_ptr_adr) != SUCCESS)
        return 0;

    if (sort_and_print_to_file(arr_ptr_adr, output_file_path) != SUCCESS)
        return 0;

    return 0;
}