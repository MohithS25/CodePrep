/* Exercise 2 — Resize
This is how std::vector grows internally. Write a function resize that takes an existing heap array, its current size, and a new (larger) size. It should allocate a new array, copy the old elements over, fill
the remaining slots with 0, free the old array, and return the new pointer. */


#include <iostream> 

int* resize(int* old_arr, int old_size, int new_size) {
    int* arr = new int[new_size]{0};
    for(int i=0 ; i<old_size ; i++){
        arr[i] = old_arr[i];
    }
    delete[] old_arr;
    return arr;
}
  
int main() {
    int* arr = new int[3]{10, 20, 30};
    arr = resize(arr, 3, 6);
  
    for (int i = 0; i < 6; i++) {
        std::cout << arr[i] << " ";   // 10 20 30 0 0 0
    }
    delete[] arr;   
}