#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/utils.h"

static int  my_strcmp         (const char *str1, const char *str2);
static int  my_strcmp_reverse (string *arr_ptr, int index1, int index2);
static void swap_string       (char **str1, char **str2);
static void swap_len          (int *len1, int *len2);
static int  partition         (string *arr_ptr, int left, int right, Sort mode);

void free_memory(poem *onegin_ptr, FILE *output_file)
{
    free(onegin_ptr->arr_ptr);
    free(onegin_ptr->text);
    fclose(output_file);
}

static void swap_string(char **str1, char **str2)
{
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    char *tmp = *str1;
    *str1  = *str2;
    *str2  =  tmp;
}

static void swap_len (int *len1, int *len2)
{
    assert(len1 != nullptr);
    assert(len2 != nullptr);

    int tmp = *len1;
    *len1 = *len2;
    *len2 = tmp;
}

static int my_strcmp(const char *str1, const char *str2)
{
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    while (not isalpha(*str1))
        str1++;

    while (not isalpha(*str2))
        str2++;

    while (tolower(*str1) == tolower(*str2) && *str1 != '\0')
    {
        str1++;
        str2++;
    }
    
    return tolower(*str1) - tolower(*str2);
}

static int my_strcmp_reverse(string *arr_ptr, int index1, int index2)
{
    assert(arr_ptr != nullptr);

    int i1 = arr_ptr[index1].len - 1;
    int i2 = arr_ptr[index2].len - 1;

    const char *str1 = arr_ptr[index1].string;
    const char *str2 = arr_ptr[index2].string;

    while (not isalpha(*(str1+i1)))
        i1--;

    while (not isalpha(*(str2+i2)))
        i2--;

    while (tolower(*(str1+i1)) == tolower(*(str2+i2)))
    {
        if (i1 < 1 || i2 < 1)
            break;
        i1--;
        i2--;
    }
    return tolower(*(str1+i1)) - tolower(*(str2+i2));
}

void my_qsort(string *arr_ptr, int left, int right, Sort mode)
{
    if (left < right)
    {
        int pi = partition(arr_ptr, left, right, mode);
        my_qsort(arr_ptr, left, pi - 1, mode);
        my_qsort(arr_ptr, pi + 1, right, mode);
    }
}

static int partition(string *arr_ptr, int left, int right, Sort mode)
{
    int i = left - 1;

    if (mode == LEFT)
        for (int j = left; j <= right - 1; j++)
            if (my_strcmp(arr_ptr[j].string, arr_ptr[right].string) < 0)
                {
                    i++;
                    swap_string (&arr_ptr[i].string, &arr_ptr[j].string);
                    swap_len    (&arr_ptr[i].len,    &arr_ptr[j].len);
                }

    if (mode == RIGHT)
        for (int j = left; j <= right - 1; j++)
            if (my_strcmp_reverse(arr_ptr, j, right) < 0)
                {
                    i++;
                    swap_string (&arr_ptr[i].string, &arr_ptr[j].string);
                    swap_len    (&arr_ptr[i].len,    &arr_ptr[j].len);
                }

    swap_string(&arr_ptr[i + 1].string, &arr_ptr[right].string);
    swap_len(&arr_ptr[i + 1].len, &arr_ptr[right].len);

    return i + 1;
}