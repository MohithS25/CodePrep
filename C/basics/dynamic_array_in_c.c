/*Exercise 1. Implement a dynamic integer array in C — a struct with a malloc-backed buffer, size, and capacity. Write int_array_create(), int_array_push(arr, val), int_array_get(arr, i), and int_array_destroy(arr). Use realloc to grow (double capacity). Handle the realloc failure correctly.
*/

#include <stdio.h>

typedef struct{
    int* data;
    size_t size;
    size_t capacity;
}IntArray;

IntArray* int_array_create(void){
    IntArray* arr = malloc(sizeof(*arr));
    if(arr == NULL){
        return NULL;
    }

    arr->size = 0;
    arr->capacity = 4;
    arr->data = malloc(arr->capacity * sizeof(*arr->data));

    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }

    return arr;
}

int int_array_push(IntArray *arr, int value) {
    if (arr == NULL) {
        return 0;
    }

    if (arr->size == arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        int *temp = realloc(arr->data, new_capacity * sizeof(*temp));

        if (temp == NULL) {
            return 0;   // old arr->data is still valid here
        }

        arr->data = temp;
        arr->capacity = new_capacity;
    }

    arr->data[arr->size] = value;
    arr->size++;
    return 1;
}

int int_array_get(const IntArray *arr, size_t i) {
    assert(arr != NULL);
    assert(i < arr->size);
    return arr->data[i];
}

void int_array_destroy(IntArray *arr) {
    if (arr == NULL) {
        return;
    }

    free(arr->data);
    free(arr);
}

int main(void) {
    IntArray *arr = int_array_create();
    if (arr == NULL) {
        fprintf(stderr, "Failed to create array\n");
        return 1;
    }

    int values[] = {5, 2, 8, 1, 9, 3};
    size_t n = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < n; i++) {
        if (!int_array_push(arr, values[i])) {
            fprintf(stderr, "Push failed\n");
            int_array_destroy(arr);
            return 1;
        }
    }

    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", int_array_get(arr, i));
    }
    printf("\n");

    int_array_destroy(arr);
    return 0;
}



