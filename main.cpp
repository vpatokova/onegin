#include <stdio.h>
#include <stdlib.h>
#include "include/io.h"
#include "include/sort.h"
#include "include/poem.h"
#include "include/common.h"
#include "include/test.h"

int main(int argc, char *argv[])
{
    if (check_param(argc, argv[1], argv[2]) != SUCCESS)
        return 1;

    const char *input_file_path  = argv[1];
    const char *output_file_path = argv[2];

    Sort_mode sort_mode = get_sort_mode(argv[3]);

    if (sort_mode == BAD_MODE)
        return 1;

    poem onegin = { 0 };

    Error_codes error_code = construct_poem(input_file_path, &onegin);

    if (error_code != SUCCESS)
        return 1;

    if (sort_mode == TEST)
    {
        error_code = test_output(output_file_path, &onegin);

        if (error_code != SUCCESS)
        {
            destruct_poem(&onegin);
            return 1;
        }
    }
    
    else // sort_mode != TEST
    {
        my_qsort(onegin.arr_ptr, 0, onegin.n_rows, sort_mode);

        write_sorted(output_file_path, &onegin);
    }

    destruct_poem(&onegin);

    return 0;
}