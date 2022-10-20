#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <stddef.h>     // definition of size_t

// allocate 256bit aligned memory
void* align_malloc(size_t size);

// free aligned memory
void free_mem(void* pmem);

#endif