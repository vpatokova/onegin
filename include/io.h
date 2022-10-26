#ifndef FILE_H
#define FILE_H

#include "common.h"
#include "sort.h"
#include "poem.h"

Sort_mode   get_sort_mode             (const char *sort_mode);
void        write_sorted              (FILE *file_out, poem *onegin_ptr);
Error_codes get_content               (const char *input_file_path,  poem *onegin_ptr);
Error_codes check_param               (int arg_count, const char *input_file_path, 
                                       const char *output_file_path);

#endif // !FILE_H