#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/utils.h"

static int  my_strcmp         (const char *str1, const char *str2);
static int  my_strcmp_reverse (string *arr_ptr, int index1, int index2);
static int  partition         (string *arr_ptr, int left, int right, Sort_mode mode);
static void swap_struct       (string *s1, string *s2);

void free_memory(poem *onegin_ptr)
{
    free(onegin_ptr->arr_ptr);
    free(onegin_ptr->text);
}

static void swap_struct(string *s1, string *s2)
{
    assert(s1 != nullptr);
    assert(s2 != nullptr);

    string tmp = *s1;
    *s1  = *s2;
    *s2  =  tmp;    
}

static int my_strcmp(const char *str1, const char *str2)
{
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    while (! isalpha(*str1))
        str1++;

    while (! isalpha(*str2))
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

    while (! isalpha(*(str1+i1)))
        i1--;

    while (! isalpha(*(str2+i2)))
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

void my_qsort(string *arr_ptr, int left, int right, Sort_mode sort_mode)
{
    if (left < right)
    {
        int pi = partition(arr_ptr, left, right, sort_mode);
        my_qsort(arr_ptr, left, pi - 1, sort_mode);
        my_qsort(arr_ptr, pi + 1, right, sort_mode);
    }
}

static int partition(string *arr_ptr, int left, int right, Sort_mode sort_mode)
{
    int i = left - 1;

    if (sort_mode == LEFT_TO_RIGHT)
        for (int j = left; j < right; j++)
            if (my_strcmp(arr_ptr[j].string, arr_ptr[right].string) < 0)
                {
                    i++;
                    swap_struct(arr_ptr + i, arr_ptr + j);
                }

    if (sort_mode == RIGHT_TO_LEFT)
        for (int j = left; j < right; j++)
            if (my_strcmp_reverse(arr_ptr, j, right) < 0)
                {
                    i++;
                    swap_struct(arr_ptr + i, arr_ptr + j);
                }

    swap_struct(arr_ptr + i + 1, arr_ptr + right);

    return i + 1;
}