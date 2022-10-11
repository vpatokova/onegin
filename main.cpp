#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "sort.h"
#include "utils.h"

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

    if (read_file(input_file_path, &onegin) != SUCCESS)
        return 0;
    if (sort_and_print_to_file(output_file_path, &onegin) != SUCCESS)
        return 0;

    return 0;
}