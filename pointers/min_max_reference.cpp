#include <iostream>

void min_max(int* arr,int size,int& min,int& max){
    min = max = arr[0];
    for(int i=0;i<size;i++){
        if(size == 1){min = max = arr[i];}
        if(arr[i]<min){
            min = arr[i];
        }
        else if(arr[i]>max){
            max = arr[i];
        }
    }
}

int main(){
    int nums[] = {5,3,1};
    int min,max;
    min_max(nums,3,min,max);
    std::cout<<"Max: "<<max<<"\nMin: "<<min<<std::endl;
    return 0;
}