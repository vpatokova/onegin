#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/io.h"
#include "../include/sort.h"
#include "../include/utils.h"
#include "../include/poem.h"

static Error_codes split_text   (poem *onegin_ptr);

Error_codes construct_poem(const char *input_file_path, poem *onegin_ptr)
{
    assert(input_file_path != nullptr);
    assert(onegin_ptr      != nullptr);

    if (get_content(input_file_path, onegin_ptr) != SUCCESS)
        return FAIL;

    if (split_text(onegin_ptr) != SUCCESS)
        return FAIL;

    return SUCCESS;
}

static Error_codes split_text(poem *onegin_ptr)
{
    assert(onegin_ptr != nullptr);
    
    for (int count = 0; count < onegin_ptr->n_chars + 1; count++)
    {
        if (onegin_ptr->text[count] == '\n')
        {
            onegin_ptr->text[count] = '\0';
            (onegin_ptr->n_rows)++;
        }
    }

    onegin_ptr->arr_ptr = (string*) calloc(onegin_ptr->n_rows + 1, sizeof(string)); 

    if (onegin_ptr->arr_ptr == nullptr)
    {
        printf("Could not find free memory.\n");
        return ERROR_BAD_CALLOC;
    }

    int row = 1;
    int count = 0;

    onegin_ptr->arr_ptr[0].string = &(onegin_ptr->text)[0];

    while (row <= onegin_ptr->n_rows)
    {
        if (onegin_ptr->text[count] == '\0')
        {
            onegin_ptr->arr_ptr[row].string = &(onegin_ptr->text)[count + 1];
            onegin_ptr->arr_ptr[row - 1].len = (onegin_ptr->arr_ptr[row].string - onegin_ptr->arr_ptr[row - 1].string - 1) / sizeof(char);

            row++;
        }
        count++;
    }
    

    assert (onegin_ptr->arr_ptr != 0);

    return SUCCESS;
}