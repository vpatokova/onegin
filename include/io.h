#ifndef FILE_H
#define FILE_H

#include "utils.h"

Error_codes fill_struct              (const char *input_file_path,  poem *onegin_ptr);
Error_codes sort_and_print_to_file (const char *output_file_path, poem *onegin_ptr);

#endif // !FILE_H