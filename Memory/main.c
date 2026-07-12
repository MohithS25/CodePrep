#include "allocator.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void) {
    // Initialize an arena pool of exactly 1KB
    if (my_allocator_init(1024) != 0) {
        printf("Allocator initialization failed!\n");
        return 1;
    }
    
    my_allocator_dump_stats();

    // Allocate three segments of different sizes
    int* arr1 = (int*)my_malloc(5 * sizeof(int));       // 20 bytes -> aligns to 24
    char* str = (char*)my_malloc(11 * sizeof(char));    // 11 bytes -> aligns to 16
    double* dbl = (double*)my_malloc(sizeof(double));   // 8 bytes  -> aligns to 8

    if (arr1) for(int i=0; i<5; i++) arr1[i] = i * 10;
    if (str) strcpy(str, "PointerMath");

    // Verify 8-byte pointer alignment explicitly
    printf("Address arr1: %p (Aligned: %s)\n", (void*)arr1, ((uintptr_t)arr1 % 8 == 0) ? "YES" : "NO");
    printf("Address str:  %p (Aligned: %s)\n", (void*)str,  ((uintptr_t)str % 8 == 0) ? "YES" : "NO");
    
    my_allocator_dump_stats();

    // Free the middle block to create a structural memory hole
    printf("\nFreeing 'str' to create a fragmentation hole...\n");
    my_free(str);
    my_allocator_dump_stats();

    // Free the first block, which should trigger coalescing with the middle block hole
    printf("\nFreeing 'arr1' to trigger contiguous memory block coalescing...\n");
    my_free(arr1);
    my_allocator_dump_stats();

    my_free(dbl);
    my_allocator_destroy();
    return 0;
}
