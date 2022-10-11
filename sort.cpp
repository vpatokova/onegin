#include <stdio.h>
#include <assert.h>
#include "sort.h"
#include "utils.h"

int  strcmp_first_letters (poem *onegin_ptr, int index1, int index2);
int  strcmp_last_letters  (poem *onegin_ptr, int index1, int index2);
void ptr_swap             (poem *onegin_ptr, int index1, int index2);

void ptr_swap(poem *onegin_ptr, int index1, int index2)
{
    assert(onegin_ptr != nullptr);

    char *tmp = onegin_ptr->arr_ptr[index1].string;
    onegin_ptr->arr_ptr[index1].string  = onegin_ptr->arr_ptr[index2].string;
    onegin_ptr->arr_ptr[index2].string  =  tmp;
}

int strcmp_first_letters(poem *onegin_ptr, int index1, int index2)
{
    assert(onegin_ptr != nullptr);

    char *str1 = onegin_ptr->arr_ptr[index1].string;
    char *str2 = onegin_ptr->arr_ptr[index2].string;

    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0')
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int strcmp_last_letters(poem *onegin_ptr, int index1, int index2)
{
    assert(onegin_ptr != nullptr);

    int len1 = onegin_ptr->arr_ptr[index1].len;
    int len2 = onegin_ptr->arr_ptr[index2].len;
    char *str1 = onegin_ptr->arr_ptr[index1].string;
    char *str2 = onegin_ptr->arr_ptr[index2].string;

    while ((str1[len1] == str2[len2]) && len1 >=0 && len2 >=0)
    {
        len1--;
        len2--;
    }
    return str1[len1] - str2[len2];
}

void my_bubble_sort_first_letters(poem *onegin_ptr)
{
    assert(onegin_ptr != nullptr);

    int i = 0, j = 0;
    for (i = 0; i < onegin_ptr->n_rows - 1; i++)
        for (j = 0; j < onegin_ptr->n_rows - 1 - i; j++)
        {
            if (strcmp_first_letters(onegin_ptr, j, j + 1) > 0)
                ptr_swap(onegin_ptr, j, j + 1);
        }
}

void my_bubble_sort_last_letters(poem *onegin_ptr)
{
    assert(onegin_ptr != nullptr);

    int i = 0, j = 0;
    for (i = 0; i < onegin_ptr->n_rows - 1; i++)
        for (j = 0; j < onegin_ptr->n_rows - 1 - i; j++)
        {
            if (strcmp_last_letters(onegin_ptr, j, j + 1) > 0)
                ptr_swap(onegin_ptr, j, j + 1);
        }
}