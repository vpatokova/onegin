#ifndef FILE_H
#define FILE_H

#include "utils.h"

ERROR_CODES read_file              (const char *input_file_path,  poem *onegin_ptr);
ERROR_CODES sort_and_print_to_file (const char *output_file_path, poem *onegin_ptr);

#endif // !FILE_H