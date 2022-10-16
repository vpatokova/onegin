#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/io.h"
#include "../include/sort.h"
#include "../include/utils.h"

static Error_codes split_text       (poem *onegin_ptr);
static long        count_chars      (FILE *file);
static void        write_arr_string (FILE *file_out, poem *onegin_ptr);
static void        print_header     (FILE *file_out, const char *word);
static void        write_origin     (FILE *file_out, poem *text);


Error_codes fill_struct(const char *input_file_path, poem *onegin_ptr)
{
    assert(input_file_path != nullptr);
    assert(onegin_ptr != nullptr);

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

    //int c = 0;
    if (fread(onegin_ptr->text, sizeof(char), onegin_ptr->n_chars, file) == 0)
    {
        printf("Could not read chars from the file.\n");
        free(onegin_ptr->text);
        fclose(file);
        return ERROR_READ_FILE;
    }

    //printf("fread: %d\n", c);
    //printf("n_chars: %d\n", onegin_ptr->n_chars);

    fclose(file);

    split_text(onegin_ptr);

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
            printf("%d %d\n", row - 1, onegin_ptr->arr_ptr[row - 1].len);
            row++;
        }
        count++;
    }
    

    assert (onegin_ptr->arr_ptr != 0);

    return SUCCESS;
}

Error_codes sort_and_print_to_file(const char *output_file_path, poem *onegin_ptr)
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
        return ERROR_OPEN_FILE;
    }

    print_header(file_out, "TEXT SORTED BY FIRST LETTERS");
    //my_bubble_sort_first_letters(onegin_ptr);
    //my_qsort(onegin_ptr->arr_ptr, onegin_ptr->arr_ptr, &onegin_ptr->arr_ptr[-1]);
    sort_qsort_first_letter(onegin_ptr);
    write_arr_string(file_out, onegin_ptr);

    /*print_header(file_out, "TEXT SORTED BY LAST LETTERS");
    my_bubble_sort_last_letters(onegin_ptr);
    write_arr_string(file_out, onegin_ptr);*/

    print_header(file_out, "SOURCE TEXT");
    write_origin(file_out, onegin_ptr);
    print_header(file_out, "END");

    free(onegin_ptr->arr_ptr);
    free(onegin_ptr->text);
    fclose(file_out);

    return SUCCESS;
}

static void write_arr_string(FILE *file_out, poem *onegin_ptr)
{
    assert(file_out   != nullptr);
    assert(onegin_ptr != nullptr);

    for (int i = 0; i < onegin_ptr->n_rows; i++)
        if (*(onegin_ptr->arr_ptr[i].string) != '\0')
            fprintf(file_out, "%s\n", onegin_ptr->arr_ptr[i].string);
}

static void write_origin (FILE *file_out, poem *text)
{
    assert (text != nullptr);
    assert (file_out != nullptr);

    char *point = text->text;

    for (int i = 0; i < text->n_rows; i++)
        point += fprintf (file_out, "%s\n", point);
}

static void print_header(FILE *file_out, const char *word) 
{
    assert(file_out != nullptr);
    assert(word != nullptr);

    fprintf(file_out, "\n\n\n------------------------------------------------------------\n\n\n");
    fprintf(file_out, "                  %s                        ", word);
    fprintf(file_out, "\n\n\n------------------------------------------------------------\n\n\n");
}
