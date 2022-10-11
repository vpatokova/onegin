#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "file.h"
#include "sort.h"
#include "utils.h"

static ERROR_CODES array_of_ptr             (poem *onegin_ptr);
static long        count_chars              (FILE *file);
static void        print_to_file_arr_string (FILE *file_out, poem *onegin_ptr);
static void        print_header             (FILE *file_out, const char* word);
static void        print_to_file_text       (FILE *file_out, poem *onegin_ptr);


ERROR_CODES read_file(const char *input_file_path, poem *onegin_ptr)
{
    assert(input_file_path != nullptr);

    FILE *file = fopen(input_file_path, "r");

    if (file == nullptr)
    {
        printf("Could not open file.\n");
        return ERROR_FILE_PATH;
    }

    onegin_ptr->n_chars = count_chars(file);

    onegin_ptr->text = (char *) calloc(onegin_ptr->n_chars + 1, sizeof(char));

    if (onegin_ptr->text == nullptr)
    {
        printf("Could not find free memory.\n");
        fclose(file);
        return ERROR_FREE_MEMORY;
    }

    if (fread(onegin_ptr->text, sizeof(char), onegin_ptr->n_chars, file) == 0)
    {
        printf("Could not read chars from the file.\n");
        free(onegin_ptr->text);
        fclose(file);
        return ERROR_READ_FILE;
    }

    fclose(file);

    array_of_ptr(onegin_ptr);

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

static ERROR_CODES array_of_ptr(poem *onegin_ptr)
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
        return ERROR_FREE_MEMORY;
    }

    onegin_ptr->arr_ptr[0].string = &(onegin_ptr->text)[0];
    int row = 1;
    int count = 0;
    while (row <= onegin_ptr->n_rows)
    {
        if (onegin_ptr->text[count] == '\0')
        {
            onegin_ptr->arr_ptr[row].string = &(onegin_ptr->text)[count + 1];
            onegin_ptr->arr_ptr[row - 1].len = (onegin_ptr->arr_ptr[row].string - onegin_ptr->arr_ptr[row - 1].string - 1) / sizeof(char);
            printf("%d %d\n", row - 1, onegin_ptr->arr_ptr[row - 1].len);
            row++;
        }
        count++;
    }
    

    assert (onegin_ptr->arr_ptr != 0);

    return SUCCESS;
}

ERROR_CODES sort_and_print_to_file(const char *output_file_path, poem *onegin_ptr)
{
    assert(output_file_path != nullptr);
    assert(onegin_ptr != nullptr);

    FILE *file_out = fopen(output_file_path, "w");

    if (file_out == nullptr)
    {
        printf("Could not open file.\n");
        free(onegin_ptr->arr_ptr);
        free(onegin_ptr->text);
        fclose(file_out);
        return ERROR_FILE_PATH;
    }

    print_header(file_out, "TEXT SORTED BY FIRST LETTERS");
    my_bubble_sort_first_letters(onegin_ptr);
    print_to_file_arr_string(file_out, onegin_ptr);

    print_header(file_out, "TEXT SORTED BY LAST LETTERS");
    my_bubble_sort_last_letters(onegin_ptr);
    print_to_file_arr_string(file_out, onegin_ptr);

    print_header(file_out, "SOURCE TEXT");
    print_to_file_text(file_out, onegin_ptr);
    print_header(file_out, "END");

    free(onegin_ptr->arr_ptr);
    free(onegin_ptr->text);
    fclose(file_out);

    return SUCCESS;
}

static void print_to_file_arr_string(FILE *file_out, poem *onegin_ptr)
{
    assert(file_out != nullptr);
    assert(onegin_ptr != nullptr);

    for (int i = 0; i < onegin_ptr->n_rows; i++)
        if (*(onegin_ptr->arr_ptr[i].string) != '\0')
            fprintf(file_out, "%s\n", onegin_ptr->arr_ptr[i].string);
}

static void print_to_file_text(FILE *file_out, poem *onegin_ptr)
{
    assert(file_out != nullptr);
    assert(onegin_ptr != nullptr);

    for (int count = 0; count < onegin_ptr->n_chars + 1; count++)
        if (onegin_ptr->text[count] == '\0')
            onegin_ptr->text[count] = '\n';

    fprintf(file_out, "%s\n", onegin_ptr->text);

}

static void print_header(FILE *file_out, const char* word) 
{
    assert(file_out != nullptr);

    fprintf(file_out, "\n\n\n------------------------------------------------------------\n\n\n");
    fprintf(file_out, "                  %s                        ", word);
    fprintf(file_out, "\n\n\n------------------------------------------------------------\n\n\n");
}
