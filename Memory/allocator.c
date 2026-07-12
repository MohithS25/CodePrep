#include "allocator.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

#define ALIGNMENT 8
// Alignment macro: rounds up 'size' to the nearest multiple of ALIGNMENT
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

// Every chunk of memory in our arena gets this tracking header immediately preceding it
typedef struct BlockHeader BlockHeader;
struct BlockHeader {
    size_t size;         // Size of the usable data block following this header (must be ALIGNed)
    bool is_free;        // Flag indicating whether this block is available
    BlockHeader* next;   // Pointer to the next structural block in physical memory
};

#define HEADER_SIZE ALIGN(sizeof(BlockHeader))

static void* global_arena_start = NULL;
static BlockHeader* free_list_head = NULL;
static pthread_mutex_t allocator_lock = PTHREAD_MUTEX_INITIALIZER;

int my_allocator_init(size_t pool_size_bytes) {
    pthread_mutex_lock(&allocator_lock);
    
    // Ensure the entire pool size requested is cleanly aligned
    size_t aligned_pool_size = ALIGN(pool_size_bytes);
    
    // Allocate the total system block we will carve up
    global_arena_start = malloc(aligned_pool_size);
    if (!global_arena_start) {
        pthread_mutex_unlock(&allocator_lock);
        return -1;
    }

    // TODO: Establish the very first master metadata block header.
    // 1. Point free_list_head to the start of global_arena_start.
    // 2. Set its size to (aligned_pool_size - HEADER_SIZE).
    // 3. Mark it as free (true), and set its next pointer to NULL.

    free_list_head = (BlockHeader*)global_arena_start;
    free_list_head->size = aligned_pool_size - HEADER_SIZE;
    free_list_head->is_free = true;
    free_list_head->next = NULL;
    
    pthread_mutex_unlock(&allocator_lock);
    return 0;
}

void* my_malloc(size_t size) {
    if (size == 0) return NULL;
    
    pthread_mutex_lock(&allocator_lock);
    
    size_t requested_size = ALIGN(size);
    BlockHeader* current = free_list_head;

    // First-Fit Search Strategy
    while (current != NULL) {
        if (current->is_free && current->size >= requested_size) {
            
            // TODO: BLOCK SPLITTING TRADEOFF
            // Check if the block is big enough to be split into two pieces.
            // It needs to have enough space left over to hold a HEADER_SIZE + at least ALIGNMENT bytes.
            // If it CAN be split:
            //   1. Create a new BlockHeader pointer positioned precisely 'requested_size' bytes after the current data start.
            //      Hint: Use raw byte math -> (char*)current + HEADER_SIZE + requested_size
            //   2. Initialize the new sub-block header (calculate its size, mark it free, link it into the chain).
            //   3. Update current block's size to requested_size, and link its next pointer to the new sub-block.

            size_t leftover = current->size - requested_size;
            if( leftover >= HEADER_SIZE + ALIGNMENT){
                BlockHeader* split = (BlockHeader*)((char*)current + HEADER_SIZE + requested_size);         
                split->size = leftover - HEADER_SIZE;
                split->is_free = true;
                split->next = current->next;
                current->size = requested_size;
                current->next = split;
            }
            
            // TODO: Mark current block as allocated and return the user-space data pointer
            // Hint: The pointer returned to the user should be shifted past the header.
            current->is_free = false;
            
            pthread_mutex_unlock(&allocator_lock);
            return (void*)((char*)current + HEADER_SIZE); // Replace with your pointer offset calculation
        }
        current = current->next;
    }

    pthread_mutex_unlock(&allocator_lock);
    return NULL; // Out of memory arena space
}

void my_free(void* ptr) {
    if (!ptr) return;

    pthread_mutex_lock(&allocator_lock);

    // TODO: POINTER BACK-STEPPING
    // Convert the user's data pointer back into a BlockHeader pointer.
    // Hint: Subtract HEADER_SIZE bytes from the incoming 'ptr' address.
    BlockHeader* header = (BlockHeader*)((char*)ptr - HEADER_SIZE);

    // Mark the block as free
    header->is_free = true;

    // TODO: COALESCING (Compacting adjacent gaps)
    // Scan the free list from the beginning (free_list_head).
    // If you encounter a block that is free, AND its next block is also free:
    //   1. Merge them by adding the next block's size and HEADER_SIZE to the current block's size.
    //   2. Skip over the next block by setting current->next = current->next->next.
    // Repeat this processing scan until no contiguous free blocks remain.

    while( header->next != NULL && header->next->is_free){
        header->size = header->size + header->next->size + HEADER_SIZE;
        header->next = header->next->next;
    }

    pthread_mutex_unlock(&allocator_lock);
}

void* my_calloc(size_t num, size_t size) {
    size_t total_bytes = num * size;
    void* ptr = my_malloc(total_bytes);
    if (ptr) {
        // TODO: Clear the allocated memory block to zero using memset
        memset(ptr, 0, total_bytes);
    }
    return ptr;
}

void my_allocator_destroy(void) {
    pthread_mutex_lock(&allocator_lock);
    free(global_arena_start);
    global_arena_start = NULL;
    free_list_head = NULL;
    pthread_mutex_unlock(&allocator_lock);
}

void my_allocator_dump_stats(void) {
    BlockHeader* current = free_list_head;
    printf("\n--- HEAP MEMORY MAP ---\n");
    while (current) {
        printf("Block Address: %p | Block Size: %lu | Status: %s | Next: %p\n",
               (void*)current, current->size, current->is_free ? "FREE" : "ALLOCATED", (void*)current->next);
        current = current->next;
    }
    printf("-----------------------\n");
}
