#include <stdio.h>
#include <assert.h>
//#include "input.h"

int main(void)
{
    const char *file_name = "test.txt";
    FILE *fp = fopen(file_name, "r");
    assert(fp != NULL);

    char mas[1000] = {0};
    char c = 0;

    for (int i = 0; i < 1000 & ((c = fgetc(fp)) != '\0'); i++)
    {
        mas[i] = c;
    }

    fclose(fp);

    for (int i = 0; i < 1000; i++)
    {
        printf("%c", mas[i]);
    }

    
    for (int i = 0; i < 1000; i++)
    {
        if (mas[i] == '\n')
            mas[i] = '\0';
    }

   
    const char *file_name_out = "C://Users//Acer//DedMipt//onegin_project//out.txt";
    FILE *fpout = fopen(file_name_out, "w");
    for (int i = 0; i < 1000; i++)
    {
        fprintf(fpout, arr[i]);
    }
    fclose(fpout);



    
    return 0;
}