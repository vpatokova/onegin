#include "file.h"
#include "sort.h"

int main(void)
{
    const char * INPUT_FILE  = "test.txt";
    const char * OUTPUT_FILE = "out.txt";
    
    read_file(INPUT_FILE);

    sort_and_print_to_file(..., OUTPUT_FILE);

    return 0;
}