#ifndef POEM_H
#define POEM_H

#include "common.h"
#include "poem.h"

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

Error_codes construct_poem (const char *input_file_path, poem *onegin_ptr);
void        destruct_poem  (poem *onegin_ptr);

#endif // !POEM_H