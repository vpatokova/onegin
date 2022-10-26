#ifndef SORT_H
#define SORT_H

#include "common.h"
#include "poem.h"

enum Sort_mode
{
    BAD_MODE      = -1,
    TEST          =  0,
    LEFT_TO_RIGHT =  1,
    RIGHT_TO_LEFT =  2
};

void my_qsort (string *arr_ptr, int left, int right, Sort_mode mode);

#endif //!SORT_H