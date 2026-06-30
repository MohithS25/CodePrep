/* Exercise 1 — Dynamic Array Builder

  Write a function make_array that allocates an array of size n on the heap, fills it with values 1 through n, and returns the pointer. The caller is responsible for cleanup. In main, use it, print it, then clean
  up correctly.
  
*/

#include <iostream>

int* make_array(int size){
    int* arr = new int[size]{0};
    for(int i=0 ; i < size ; i++ ){
        arr[i] = i+1;
    }
    return arr;
}

int main() {
   int* arr = make_array(5);
   for(int i=0 ; i<5 ; i++){
    std::cout << arr[i] << " ";
   }
   delete[] arr;
   return 0;
}