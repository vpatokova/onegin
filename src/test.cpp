#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/io.h"
#include "../include/sort.h"
#include "../include/common.h"
#include "../include/test.h"
#include "../include/poem.h"

static void print_header  (FILE *file_out, const char *word);
static void write_origin  (FILE *file_out, poem *text);
static void write_to_file (FILE *file_out, poem *onegin_ptr);

Error_codes test_output(const char *output_file_path, poem *onegin_ptr)
{
    assert(output_file_path != nullptr);
    assert(onegin_ptr       != nullptr);

    FILE *file_out = fopen(output_file_path, "w");

    if (file_out == nullptr)
    {
        printf("Could not open file.\n");
        return ERROR_OPEN_FILE;
    }

    print_header(file_out, "TEXT SORTED BY FIRST LETTERS");
    my_qsort(onegin_ptr->arr_ptr, 0, onegin_ptr->n_rows, LEFT_TO_RIGHT);
    write_to_file(file_out, onegin_ptr);

    print_header(file_out, "TEXT SORTED BY LAST LETTERS");
    my_qsort(onegin_ptr->arr_ptr, 0, onegin_ptr->n_rows, RIGHT_TO_LEFT);
    write_to_file(file_out, onegin_ptr);

    print_header(file_out, "SOURCE TEXT");
    write_origin(file_out, onegin_ptr);
    print_header(file_out, "END");

    fclose(file_out);

    return SUCCESS;    
}

static void write_to_file(FILE *file_out, poem *onegin_ptr)
{
    assert(onegin_ptr != nullptr);
    assert(file_out   != nullptr && "Could not write to file\n");

    for (int i = 0; i < onegin_ptr->n_rows; i++)
        if (*(onegin_ptr->arr_ptr[i].string) != '\0')
            fprintf(file_out, "%s\n", onegin_ptr->arr_ptr[i].string);    
}

static void write_origin(FILE *file_out, poem *text)
{
    assert (text     != nullptr);
    assert (file_out != nullptr);

    char *point = text->text;

    for (int i = 0; i < text->n_rows; i++)
        point += fprintf (file_out, "%s\n", point);
}

static void print_header(FILE *file_out, const char *word) 
{
    assert(file_out != nullptr);
    assert(word     != nullptr);

    fprintf(file_out, "\n\n\n------------------------------------------------------------\n\n\n");
    fprintf(file_out, "                     %s                    ", word);
    fprintf(file_out, "\n\n\n------------------------------------------------------------\n\n\n");
}