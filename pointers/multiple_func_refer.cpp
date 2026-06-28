#include <iostream>

// 1. Prints the value — doesn't modify it
  void print_value(const int& x) {
      std::cout << x << "\n";
  }
  //Reason - Since it just prints and doesn't modify we can reference the original value but keep it constant

  // 2. Doubles the value in place — modifies the original
  void double_in_place(int& x) {
      x = x * 2;
  }
//Reason - Since we are modifying the original value we are passing the reference to that

  // 3. Searches array — might find nothing (needs to communicate "not found")
  int* search(int* arr, int size, int target)
  // This one is already using a pointer return — explain WHY a reference
  // return wouldn't work here, even though references are generally preferred
  // Reason -> Since we are searching the array there is a possibility we can't find the element passing a reference needs a guaranteed value to return
  {
    for(int i=0; i<size; i++){
        if(arr[i]==target){
            return &arr[i];
        }
    }
    return nullptr;
  }

  int main(){
    int x = 10;
    print_value(x);
    double_in_place(x);
    std::cout << "Double: "<< x << std::endl;
    int nums[]={2,3,4,6,7,8,9};
    int* result = search(nums,7,6);
   // result = search(nums,7,10);
    if(result != nullptr){
        std::cout<<"Found: "<<*result<<std::endl;
    }
    else{
        std::cout<<"Not found"<<std::endl;
    }
    result = search(nums,7,10);
    return 0;

  }