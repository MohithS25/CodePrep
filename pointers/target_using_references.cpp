#include <iostream>

void find(int* arr, int size, int key, bool& found, int& value){
    
    found = false;
    for(int i=0;i<size;i++){
        if(arr[i] == key){
            found = true;
            value = arr[i];
            return ;
        }
    } 
}

int main(){
    int nums[] = {4,8,15,16,23,42};
    bool found;
    int value;
    find(nums,6,15,found,value);
    if (found) {
        std::cout << "Found: " << value << "\n";   
    }    
   find(nums, 6, 99, found, value);
    if (!found) {
        std::cout << "Not found\n";               
    }
}
