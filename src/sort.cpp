#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/utils.h"

int  strcmp_first_letters (const void *t, const void *s);
//static int  strcmp_last_letters  (string *arr_ptr, int index1, int index2);
static void ptr_swap             (char **str1, char **str2);

static void ptr_swap(char **str1, char **str2)
{
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    char *tmp = *str1;
    *str1  = *str2;
    *str2  =  tmp;
}

int strcmp_first_letters(const void *t, const void *s)
{
    const char *str1 = (const char *) t;
    const char *str2 = (const char *) s;
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

/*static int strcmp_last_letters(string *arr_ptr, int index1, int index2)
{
    assert(arr_ptr != nullptr);

    int i1 = arr_ptr[index1].len - 1;
    int i2 = arr_ptr[index2].len - 1;

    char *str1 = arr_ptr[index1].string;
    char *str2 = arr_ptr[index2].string;

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
}*/

void  sort_qsort_first_letter(poem *text)
{
    qsort(text->arr_ptr, text->n_rows, sizeof(string), strcmp_first_letters);
}

/*void my_qsort(string *arr_ptr, string *left, string *right)
{
    string *piv_ptr = left + (right - left)/ 2;
    //string *left = arr_ptr;
    //string *right = &arr_ptr[-1];

    while (left <= right)
    {
        while (strcmp_first_letters(left->string, piv_ptr->string) < 0)
            left++;
        
        while (strcmp_first_letters(piv_ptr->string, right->string) < 0)
            right--;

        if (left < right)
        {
            ptr_swap(&(left->string), &(right->string));

            left++;
            right--;
        }
    }

    if (right > arr_ptr)
        my_qsort(arr_ptr, arr_ptr, right);

    if (left < &arr_ptr[-1])
        my_qsort(arr_ptr, left, &arr_ptr[-1]);
}*/

/*void my_bubble_sort_first_letters(poem *onegin_ptr)
{
    assert(onegin_ptr != nullptr);

    for (int i = 0; i < onegin_ptr->n_rows - 1; i++)
        for (int j = 0; j < onegin_ptr->n_rows - 1 - i; j++)
            if (strcmp_first_letters(onegin_ptr->arr_ptr, j, j + 1) > 0)
                ptr_swap(&onegin_ptr->arr_ptr[j].string, &onegin_ptr->arr_ptr[j+1].string);
}*/

/*void my_bubble_sort_last_letters(poem *onegin_ptr)
{
    assert(onegin_ptr != nullptr);

    for (int i = 0; i < onegin_ptr->n_rows - 1; i++)
        for (int j = 0; j < onegin_ptr->n_rows - 1 - i; j++)
            if (strcmp_last_letters(onegin_ptr->arr_ptr, j, j + 1) > 0)
                ptr_swap(&onegin_ptr->arr_ptr[j].string, &onegin_ptr->arr_ptr[j+1].string);
}*/