/*
Coding Exercise

  Three functions, each demonstrating the correct use of one const form. Write their signatures, implement them, and include a comment explaining what the const prevents:

  // 1. Takes an array and prints its sum — should not modify the array
  

  // 2. Takes a pointer to a counter and increments it — pointer itself must not change
  

  // 3. Takes a pointer to a config value — neither the pointer nor the value should change
  
*/

#include <iostream>

void printSum(const int* arr, int size){
    int sum = 0;
    for(int i = 0 ; i < size ; i++){
        sum += arr[i];
    }
    std::cout << "Sum: " << sum << '\n';
}

void increment(int* const counter){
    (*counter)++;
    std::cout << "Counter = " << *counter << '\n';
}

void printConfig(const int* const config)
{
    std::cout << "Config = " << *config << '\n';
}


int main(){
    int arr[5] = {10,20,30,40,50};
    printSum(arr,5);

    int counter = 0;
    increment(&counter);
    
    const int config = 100;
    printConfig(&config);

    return 0;
}