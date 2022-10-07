#include "ERROR_CODES.h"

#ifndef FILE_H
#define FILE_H

ERROR_CODES read_file (const char *input_file_path, char ****arr_ptr_adr_x2);
ERROR_CODES sort_and_print_to_file(char ***arr_ptr_adr, const char *output_file_path);

#endif // !FILE_H