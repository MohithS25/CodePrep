#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

// Initializes the global backing arena memory pool
int  my_allocator_init(size_t pool_size_bytes);
void my_allocator_destroy(void);

// Core Allocation API matching standard C behavior
void* my_malloc(size_t size);
void* my_calloc(size_t num, size_t size);
void  my_free(void* ptr);

// Debug tool: Prints the structural state of the heap blocks
void  my_allocator_dump_stats(void);

#endif // ALLOCATOR_H