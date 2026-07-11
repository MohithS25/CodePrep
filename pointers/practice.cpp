#include <iostream>

int* find(int* arr,int size, int key){
    for(int i=0;i<size;i++){
        if(arr[i] == key){
            return &arr[i];
        }
    }
    return nullptr;
}

int main(){
    
    int nums[] = {4,8,15,16,23,42};
    int* result = find(nums,6,15);
    if(result != nullptr){
        std::cout<<"Found: "<<(*result)<<std::endl;
    }
    result = find(nums,6,99);
    if(result == nullptr)
    {
        std::cout<<"Not found"<<std::endl;
    }

    return 0;
}