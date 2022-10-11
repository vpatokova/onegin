#ifndef UTILS_H
#define UTILS_H

enum ERROR_CODES //большие буквы??
{
    ERROR_FILE_PATH   = -1,
    ERROR_FREE_MEMORY =  0,
    ERROR_READ_FILE   =  1,
    SUCCESS           =  2
};

typedef struct 
{
    char *string;
    int len;
} string;

typedef struct
{
    char *text;
    string *arr_ptr;
    int n_rows;
    int n_chars;
} poem;

#endif // !UTILS_H