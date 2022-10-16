#ifndef UTILS_H
#define UTILS_H

enum Error_codes
{
    SUCCESS           = 0,
    ERROR_OPEN_FILE   = 1,
    ERROR_BAD_CALLOC  = 2,
    ERROR_READ_FILE   = 3
};

typedef struct 
{
    char *string;
    int   len;
} string;

typedef struct
{
    char   *text;
    string *arr_ptr;
    int     n_rows;
    int     n_chars;
} poem;

#endif // !UTILS_H