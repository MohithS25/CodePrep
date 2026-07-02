/*Exercise 2 — my_for_each
  Write a my_for_each(int* arr, int n, void(*fn)(int)) that calls fn on each element. Then write three functions to pass to it: print_val, print_doubled, and print_squared. Call all three on the same array.
*/

#include <iostream>

using BinaryOp = void(*)(int);

void my_for_each(int* arr, int n, BinaryOp op){
    for(int i = 0; i < n ; i++){
        op(arr[i]);
    }
    std::cout << '\n';
}

void print_val(int x){
    std::cout << x << " ";
}
void print_doubled(int x){
    std::cout << x * 2 << " ";
}
void print_squared(int x){
    std::cout << x * x << " ";
}

int main(){
    int nums[5] = {10 ,20, 30, 40, 50};
    my_for_each(nums,5,print_val);
    my_for_each(nums,5,print_doubled);
    my_for_each(nums,5,print_squared);

    return 0;
}