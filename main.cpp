#include <stdio.h>
#include <stdlib.h>
#include "include/io.h"
#include "include/sort.h"
#include "include/poem.h"
#include "include/utils.h"
#include "include/test.h"

int main(int argc, char *argv[])
{
    if (check_param(argc, argv[1], argv[2], argv[3]) != SUCCESS)
        return 1;

    const char *input_file_path  = argv[1];
    const char *output_file_path = argv[2];

    Sort_mode sort_mode = get_sort_mode(argv[3]);

    poem onegin = 
    {
        .text    = nullptr,
        .arr_ptr = nullptr,
        .n_rows  =       1,
        .n_chars =       0,
    };

    if (construct_poem(input_file_path, &onegin) != SUCCESS)
        return 1;
    
    if (sort_mode == TEST)
    {
        if (test_output(output_file_path, &onegin) != SUCCESS)
            return 1;
    }
    
    else // sort_mode != TEST
        if (write_to_file_sorted_text(output_file_path, &onegin, sort_mode) != SUCCESS)
            return 1;

    return 0;
}