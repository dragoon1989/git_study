#include "utility.h"

#include <stdlib.h>

void* align_malloc(size_t size)
{
    return _aligned_malloc(size, 64);
}

void free_mem(void* pmem)
{
    _aligned_free(pmem);
}