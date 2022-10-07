#include <stdio.h>
#include "sort.h"
#include "ERROR_CODES.h"

int strcmp_first_letters(const char *str1, const char *str2);
void ptr_swap(char *str1, char *str2);

void ptr_swap(char *str1, char *str2)
{

        char *tmp = str1;
        str1  = str2;
        str2  =  tmp;

}

int strcmp_first_letters(const char *str1, const char *str2)
{
    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0')
 {
        str1++;
        str2++;
    }
    return *str1 - *str2;
    
}

void my_bubble_sort(char ***arr_ptr_adr, int n_rows)
{
    int i = 0, j = 0;
    for (i = 0; i < n_rows - 1; i++)
        for (j = 0; j < n_rows - 1 - i; j++)
        {
            if (strcmp_first_letters(*(*arr_ptr_adr + j), *(*arr_ptr_adr + j + 1)) > 0)
                ptr_swap(*(*arr_ptr_adr + j), *(*arr_ptr_adr + j));
        }
}