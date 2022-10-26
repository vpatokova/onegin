#ifndef COMMON_H
#define COMMON_H

enum Error_codes
{
    SUCCESS           = 0,
    ERROR_OPEN_FILE   = 1,
    ERROR_BAD_CALLOC  = 2,
    ERROR_READ_FILE   = 3,
    WRONG_EXTENSION   = 4,
    BAD_USER_INPUT    = 5
};

#endif // !COMMON_H