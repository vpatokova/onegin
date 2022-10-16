#include <stdio.h>
#include <stdlib.h>
#include "include/io.h"
#include "include/sort.h"
#include "include/utils.h"

int main(void)
{
    const char *input_file_path  = "test.txt";
    const char *output_file_path = "out.txt";

    poem onegin = 
    {
        .text    = nullptr,
        .arr_ptr = nullptr,
        .n_rows  =       1,
        .n_chars =       0,
    };

    if (fill_struct(input_file_path, &onegin) != SUCCESS)
        return 1;
    if (sort_and_print_to_file(output_file_path, &onegin) != SUCCESS)
        return 1;

    return 0;
}