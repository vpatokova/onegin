#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/io.h"
#include "../include/sort.h"
#include "../include/utils.h"
#include "../include/test.h"

static void print_header (FILE *file_out, const char *word);
static void write_origin (FILE *file_out, poem *text);

Error_codes test_output(const char *output_file_path, poem *onegin_ptr)
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

    print_header(file_out, "TEXT SORTED BY FIRST LETTERS");
    my_qsort(onegin_ptr->arr_ptr, 0, onegin_ptr->n_rows, LEFT_TO_RIGHT);
    write_sorted(file_out, onegin_ptr);

    print_header(file_out, "TEXT SORTED BY LAST LETTERS");
    my_qsort(onegin_ptr->arr_ptr, 0, onegin_ptr->n_rows - 1, RIGHT_TO_LEFT);
    write_sorted(file_out, onegin_ptr);

    print_header(file_out, "SOURCE TEXT");
    write_origin(file_out, onegin_ptr);
    print_header(file_out, "END");

    free_memory(onegin_ptr);
    fclose(file_out);

    return SUCCESS;    
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