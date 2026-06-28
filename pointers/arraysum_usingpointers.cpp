#include <iostream>

int array_sum(int* arr, int size){                //pointer to arr, size -> args
    int sum = 0;
    for(int* p=arr;p<arr+size;p++){               //using p -> arr[0] and until sizeof array, p+1 -> *(arr+1) -> arr[1]
        sum += *p;
    }
    return sum;
}

int main(){
    int arr[5] = {10,20,30,40,50};
    int size = (sizeof(arr)/sizeof(arr[0]));             //total size/sizeof first ele = number of elements
    std::cout<<array_sum(arr,size)<<std::endl;           //addr of array, size -> args

    return 0;
    
}