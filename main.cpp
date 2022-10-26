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

    poem onegin = {};

    Error_codes error_code = construct_poem(input_file_path, &onegin);

    if (error_code != SUCCESS)
        return 1;
    
    FILE *file_out = fopen(output_file_path, "w");

    if (file_out == nullptr)
    {
        printf("Could not open file.\n");
        return ERROR_OPEN_FILE;
    }

    if (sort_mode == TEST)
    {
        error_code = test_output(file_out, &onegin);

        if (error_code != SUCCESS)
        {
            destruct_poem(&onegin);
            fclose(file_out);
            return 1;
        }
    }
    
    else // sort_mode != TEST
    {
        my_qsort(onegin.arr_ptr, 0, onegin.n_rows, sort_mode);

        write_sorted(file_out, &onegin);
    }

    destruct_poem(&onegin);
    fclose(file_out);

    return 0;
}