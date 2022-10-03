#include "file.h"

void read_file(const char * INPUT_FILE_NAME)
{
    FILE *file = fopen(INPUT_FILE_NAME, "r");

    if (file == NULL)
        printf("Could not open file.\n");
    assert(file != NULL);

    const long int SYMBOLS = count_symbols(file);

    char * arr = (char *) calloc(SYMBOLS + 1, sizeof(char));

    if (arr == NULL)
        printf("Could not find free memory.\n");
    assert(arr != NULL);

    fread(arr, sizeof(char), SYMBOLS, file); //двоичный код??

    fclose(file);

    text_normalize(arr, SYMBOLS); // хочу получить массив из указателей на строки
}

static long int count_symbols(FILE *file)
{
    fseek(file, 0L, SEEK_END);

    long int number = ftell(file);

    fseek(file, 0L, SEEK_SET);
}

static void text_normalize(char * arr, int SYMBOLS)
{
    for (int count = 0; count < SYMBOLS + 1; count++)
    {
        if (arr[count] = '\n')
            arr[count] = '\0';
    }
    // ..., что-то делаю дальше и получаю массив из указателей
}

