#ifndef FILE_H
#define FILE_H

void              read_file     (const char * TEXT);
static long int   count_symbols (FILE *file);
static void       text_normalize(char * arr, int SYMBOLS);

#endif // !FILE_H