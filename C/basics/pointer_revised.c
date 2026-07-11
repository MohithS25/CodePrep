/*Exercise 1. Write void reverse(int* arr, int n) that reverses an array in place using only pointer arithmetic — no arr[i] subscript notation allowed. Use two pointers starting at each end and walk inward. Test it with {1, 2, 3, 4, 5}.

#include <stdio.h>

void reverse(int* arr, int n){
    int* p = arr;
    int* q = (arr+(n-1));
    while(p < q){
        int temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
    }
}

int main(){
    int arr[] = {1, 2, 3, 4, 5};
    reverse(arr, 5);
    for(int i=0 ; i < 5 ; i++){
        printf("%d ", *(arr + i));
    }
}

*/

/* Exercise 2. Write int* find(int* arr, int n, int target) that searches an array and returns a pointer to the first matching element, or NULL if not found. In main, use the returned pointer to modify the found element in place (double it). Use pointer arithmetic, not index notation.

#include <stdio.h>

int* find(int* arr, int n, int target){
    for(int i=0 ; i<n ; i++){
        if((*(arr + i)) == target){
            return (arr + i);
        }
    }

    return NULL;
}

int main(){
    int arr[] = {1, 4, 3, 4, 5};
    int* p = find(arr, 5, 0);
    if(p != NULL){
    *p *= 2;
    }
    for(int i=0 ; i < 5 ; i++){
        printf("%d ", *(arr + i));
    }
    return 0;
}
*/

/*
Exercise 3. Write a function void str_reverse(char* s) that reverses a string in place. You'll need to find the end first (walk to '\0'), then use two pointers to swap characters inward. Test it with "hello" — should produce "olleh".

#include <stdio.h>
#include <string.h>

void str_reverse(char* s) {
    char* p = s;
    char* q = s;
    while (*q != '\0') q++;   
    q--;                       
    while (p < q) {
        char temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
    }
}

int main(){
    char s[] = "hello";
    str_reverse(s);
    printf("%s", s);
    return 0;
}
*/

/*
Exercise 4. Write int** make_matrix(int rows, int cols) that allocates a 2D integer matrix on the heap — an array of rows pointers, each pointing to a cols-element int array. Fill it so matrix[i][j] = i * cols + j. Print it in main, then free all the memory properly (inner arrays first, then the outer array).
*/

#include <stdio.h>
#include <stdlib.h>

// Creates a rows x cols matrix
int **make_matrix(int rows, int cols) {
    int **matrix = malloc(rows * sizeof(int *));

    if (matrix == NULL) {
        return NULL;
    }

    // Allocate each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));

        if (matrix[i] == NULL) {
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }

        // Fill the row
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }

    return matrix;
}

int main(void) {
    int rows = 3;
    int cols = 4;

    int **matrix = make_matrix(rows, cols);

    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Print the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free each row
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    // Free the array of row pointers
    free(matrix);

    return 0;
}