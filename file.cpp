#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "file.h"
#include "sort.h"
#include "ERROR_CODES.h"

static long    count_chars  (FILE *file);
static ERROR_CODES array_of_ptr (char *arr_buf, long n_chars, char ****arr_ptr_adr);
static int count_rows(char ***arr_ptr_adr);

ERROR_CODES read_file(const char *input_file_path, char ****arr_ptr_adr_x2)
{
    assert(input_file_path != nullptr);

    FILE *file = fopen(input_file_path, "r");

    if (file == nullptr)
    {
        printf("Could not open file.\n");
        return ERROR_FILE_PATH;
    }

    long n_chars = count_chars(file);
    printf("n_chars: %ld\n", n_chars);

    char *arr_buf = (char *) calloc(n_chars + 1, sizeof(char));

    if (arr_buf == nullptr)
    {
        printf("Could not find free memory.\n");
        fclose(file);
        return ERROR_FREE_MEMORY;
    }

    if (fread(arr_buf, sizeof(char), n_chars, file) == 0)
    {
        printf("Could not read chars from the file.\n");
        free(arr_buf);
        fclose(file);
        return ERROR_READ_FILE;
    }

    printf("%s\n", arr_buf);

    fclose(file);

    array_of_ptr(arr_buf, n_chars, arr_ptr_adr_x2);

    assert (*arr_ptr_adr_x2 != 0);

    return SUCCESS;
}

static long count_chars(FILE *file)
{
    assert(file != nullptr);

    long start_point = ftell(file);

    fseek(file, 0L, SEEK_END);

    long n_chars = ftell(file) - start_point; //норм, что переменные n_chars названы одинаково?

    fseek(file, start_point, SEEK_SET);

    return n_chars;
}

static int count_rows(char ***arr_ptr_adr)
{
    assert(arr_ptr_adr != nullptr);

    //int n_rows = 0;

    printf("%d", sizeof(*arr_ptr_adr) / sizeof(*arr_ptr_adr[0]));

    return sizeof(*arr_ptr_adr) / sizeof(*arr_ptr_adr[0]);
}

static ERROR_CODES array_of_ptr(char *arr_buf, long n_chars, char ****arr_ptr_adr)
{
    assert(arr_buf != nullptr);
    
    int n_zero = 0;
    for (int count = 0; count < n_chars + 1; count++)
    {
        if (arr_buf[count] == '\n')
        {
            arr_buf[count] = '\0';
            n_zero++;
        }
    }
    printf("n_zero: %d\n", n_zero);
    char **arr_ptr = (char **) calloc(n_zero + 1, sizeof(char *)); 

    if (arr_ptr == nullptr)
    {
        printf("Could not find free memory.\n");
        return ERROR_FREE_MEMORY;
    }

    int i = 0;
    for (int count = 0; count < n_chars + 1; count++)
    {
        if (arr_buf[count] == '\0')
        {
            arr_ptr[i] = arr_buf + count + 1;
            i++;
        }
    }

    *arr_ptr_adr = &arr_ptr;

    return SUCCESS;
}

ERROR_CODES sort_and_print_to_file(char ***arr_ptr_adr, const char *output_file_path)
{
    assert(output_file_path != nullptr);
    assert(arr_ptr_adr != nullptr);

    FILE *file_out = fopen(output_file_path, "w");

    if (file_out == nullptr)
    {
        printf("Could not open file.\n");
        free(**arr_ptr_adr);
        free(*arr_ptr_adr);
        fclose(file_out);
        return ERROR_FILE_PATH;
    }

    int n_rows = count_rows(arr_ptr_adr) + 1;

    my_bubble_sort(arr_ptr_adr, n_rows);

    for (int i = 0; i < n_rows; i++)
        fprintf(file_out, "%s", *(*arr_ptr_adr + i));
        //fputs(*arr_ptr + i, file_out);

    fclose(file_out);

    return SUCCESS;
}

