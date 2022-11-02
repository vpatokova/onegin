#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/io.h"
#include "../include/sort.h"
#include "../include/common.h"
#include "../include/poem.h"
#include "../include/config.h"

static long count_chars (FILE *file);

Error_codes check_param(int arg_count, const char *input_file_path, 
                        const char *output_file_path)
{
    if (arg_count != 4)
    {
        printf("Incorrect number of arguments\n\n" \
               "Example of correct input:\n \\.prog input_file.txt output_file.txt sort_mode\n\n");
        return BAD_USER_INPUT;
    }

    if (strcmp(input_file_path, output_file_path) == 0)
    {
        printf("Names of input and output files should be different.\n");
        return BAD_USER_INPUT;
    }

    return SUCCESS;
}

Sort_mode get_sort_mode (const char *sort_mode)
{
    if (strcmp(sort_mode, left_to_right_mode) == 0)
        return LEFT_TO_RIGHT;

    if (strcmp(sort_mode, right_to_left_mode) == 0)
        return RIGHT_TO_LEFT;

    if (strcmp(sort_mode, test_mode) == 0)
        return TEST;
    
    printf("Incorrect sort mode. Use:\n"             
           "'%s' to test this program,\n"          
           "'%s' to sort text from left to right,\n" 
           "'%s' to sort text from right to left.\n",
           test_mode, left_to_right_mode, right_to_left_mode);

    return BAD_MODE;
}

Error_codes get_content(const char *input_file_path, poem *onegin_ptr)
{
    assert(input_file_path != nullptr);
    assert(onegin_ptr      != nullptr);

    FILE *file = fopen(input_file_path, "r");

    if (file == nullptr)
    {
        printf("Could not open file.\n");
        return ERROR_OPEN_FILE;
    }

    onegin_ptr->n_chars = count_chars(file);

    onegin_ptr->text = (char *) calloc(onegin_ptr->n_chars + 1, sizeof(char));

    if (onegin_ptr->text == nullptr)
    {
        printf("Could not find free memory.\n");
        fclose(file);
        return ERROR_BAD_CALLOC;
    }

    if (fread(onegin_ptr->text, sizeof(char), onegin_ptr->n_chars, file) == 0)
    {
        printf("Could not read chars from the file.\n");
        free(onegin_ptr->text);
        fclose(file);
        return ERROR_READ_FILE;
    }

    fclose(file);

    return SUCCESS;
}

static long count_chars(FILE *file)
{
    assert(file != nullptr);

    long start_point = ftell(file);

    fseek(file, 0L, SEEK_END);

    long n_chars = ftell(file) - start_point;

    fseek(file, start_point, SEEK_SET);

    return n_chars;
}

void write_sorted(const char *output_file_path, poem *onegin_ptr)
{
    assert(output_file_path != nullptr);
    assert(onegin_ptr       != nullptr);

    FILE *file_out = fopen(output_file_path, "w");

    assert(file_out != nullptr && "Could not write to file\n");

    for (int i = 0; i < onegin_ptr->n_rows; i++)
        if (*(onegin_ptr->arr_ptr[i].string) != '\0')
            fprintf(file_out, "%s\n", onegin_ptr->arr_ptr[i].string);

    fclose(file_out);
}

