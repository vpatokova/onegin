#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/io.h"
#include "../include/sort.h"
#include "../include/utils.h"

static Error_codes check_extension (const char *file_name, const char *extension);
static long        count_chars     (FILE *file);

Error_codes check_param(int arg_count, const char *input_file_path, 
                        const char *output_file_path, const char *sort_mode)
{
    if (arg_count != 4)
    {
        printf("Incorrect number of arguments\n\n" \
               "Example of correct input:\n \\.prog input_file.txt output_file.txt sort_mode\n\n");
        return FAIL;
    }

    else if (strcmp(input_file_path, output_file_path) == 0)
    {
        printf("Names of input and output files should be different.\n");
        return FAIL;
    }

    else if ((check_extension(input_file_path,  "txt") == WRONG_EXTENSION) or
             (check_extension(output_file_path, "txt") == WRONG_EXTENSION))
    {
        printf("Files should have the .txt extension.\n");
        return FAIL;
    }

    else if (strcmp(sort_mode, "test") != 0 and
             strcmp(sort_mode, "lr") != 0 and 
             strcmp(sort_mode, "rl") != 0)
    {
        printf("Incorrect sort mode. Use:\n"             \
               "'test' to test this program,\n"          \
               "'lr' to sort text from left to right,\n" \
               "'rl' to sort text from right to left.\n");
        return FAIL;
    }

    return SUCCESS;
}

static Error_codes check_extension (const char *file_name, const char *extension)
{
    if (strchr(file_name, '.') == nullptr)
        return WRONG_EXTENSION;

    else if (strcmp(strchr(file_name, '.') + 1, extension) != 0)
        return WRONG_EXTENSION;
 
    return SUCCESS;
}

Sort_mode get_sort_mode (const char *sort_mode)
{
    if (strcmp(sort_mode, "lr") == 0)
        return LEFT_TO_RIGHT;

    else if (strcmp(sort_mode, "rl") == 0)
        return RIGHT_TO_LEFT;

    else // if (strcmp(sort_mode, "test") == 0)
        return TEST;
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

Error_codes write_to_file_sorted_text(const char *output_file_path, poem *onegin_ptr, Sort_mode sort_mode)
{
    assert(output_file_path != nullptr);
    assert(onegin_ptr       != nullptr);

    FILE *file_out = fopen(output_file_path, "w");

    if (file_out == nullptr)
    {
        printf("Could not open file.\n");
        free_memory(onegin_ptr);
        fclose(file_out);
        return ERROR_OPEN_FILE;
    }

    my_qsort(onegin_ptr->arr_ptr, 0, onegin_ptr->n_rows, sort_mode);
    write_sorted(file_out, onegin_ptr);

    free_memory(onegin_ptr);
    fclose(file_out);

    return SUCCESS;
}

void write_sorted(FILE *file_out, poem *onegin_ptr)
{
    assert(file_out   != nullptr);
    assert(onegin_ptr != nullptr);

    for (int i = 0; i < onegin_ptr->n_rows; i++)
        if (*(onegin_ptr->arr_ptr[i].string) != '\0')
            fprintf(file_out, "%s\n", onegin_ptr->arr_ptr[i].string);
}

