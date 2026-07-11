#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int num1 = *(const int *)a;
    int num2 = *(const int *)b;

    return (num1 > num2) - (num1 < num2);
}

int main() {
    int arr[] = {5, 2, 8, 1, 9, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sort the array
    qsort(arr, n, sizeof(int), compare);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}