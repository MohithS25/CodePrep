/*
 Exercise 3 — Sorting with a comparator

  Write my_sort(int* arr, int n, bool(*cmp)(int, int)) — a simple bubble sort that uses cmp to decide ordering. Then write two comparators:
  - ascending(int a, int b) — returns true if a < b
  - descending(int a, int b) — returns true if a > b

  Sort the same array both ways using the same my_sort function. No std::sort.
*/

#include <iostream>

void my_sort(int* arr, int n, bool(*cmp)(int, int)){
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (!cmp(arr[j], arr[j + 1]))
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

bool ascending(int a, int b){
    return a < b;
}

bool descending(int a, int b){
    return a > b;
}

void print(int* arr, int n){
    for(int i = 0; i < n; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

int main(){
    int nums[5] = {35, 12, 64, 23, 54};
    my_sort(nums,5,ascending);
    print(nums, 5);
    my_sort(nums,5,descending);
    print(nums, 5);
    return 0;
}