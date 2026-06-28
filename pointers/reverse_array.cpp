#include <iostream>

void reverse_array(int* arr, int size){
    int* p = arr;                          //points to arr[0]
    int* q = arr + (size-1);               // points to arr[size-1]

    for(int x=0;x<(size/2);x++){           //swap the first and last, p+1 -> q-1
        int temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
    }
}

int main(){
    int arr[5] = {1,2,3,4,5};
    reverse_array(arr,5);
    for(int i=0; i<5;i++){
        std::cout<<arr[i]<<" ";
    }

    return 0;
}