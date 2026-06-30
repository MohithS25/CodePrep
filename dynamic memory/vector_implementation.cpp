/*Exercise — Build a Mini Dynamic Integer Array

  Implement a simple dynamic integer array from scratch, similar to how std::vector<int> works internally. You decide the struct layout, function names, and how to test it.

  It must support:

  1. Creation — starts with a heap-allocated array of capacity 4, size 0
  2. Push back — appends an integer to the end. If the array is full, double the capacity before inserting. This growth must use your own my_memcpy internally (non-overlapping — new allocation)
  3. Insert at index — inserts an integer at a given position, shifting everything from that position rightward by one slot to make room. If full, grow first. The shift must use my_memmove — think carefully about
  why memcpy would be wrong here
  4. Print — prints all current elements
  5. Destroy — cleans up all heap memory correctly
  
  Your test in main must:
  - Push 5 values to trigger at least one resize
  - Insert a value in the middle
  - Print the result and verify it looks correct
  - Clean up with no leaks */

#include <iostream>

// creating the struct for array
struct Array{
    int* data;
    size_t size;
    size_t capacity;
};

// initializing the array with size = 0 , cap = 4
void init(Array& arr){
    arr.size = 0;
    arr.capacity = 4;
    arr.data = new int[arr.capacity];
}

//destroy array
void destroy(Array& arr){
    delete[] arr.data;
    arr.size = 0;
    arr.capacity = 0;
    arr.data = nullptr;
}

//memcpy for resize
void* my_memcpy(void* dst, const void* src, size_t n){
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;
    for(size_t i = 0; i < n ; i++){
        d[i] = s[i];
    }
    return dst;
}

//memmove for insert at a position
void* my_memmove(void* dst, const void* src, size_t n){
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;
    if(d == s){
        return dst;
    }
    if(d<s){
        for(size_t i=0; i<n ; i++){
            d[i] = s[i];
        }
    }
    else if(d>s){
        for(size_t i=n ; i>0 ; i--){
            d[i-1] = s[i-1];
        }
    }
    return dst;
}

//resize the array
void resize(Array& arr){
    size_t new_capacity = arr.capacity * 2;
    int* new_data = new int[new_capacity];
    my_memcpy(new_data, arr.data, arr.size * sizeof(int));
    delete[] arr.data;
    arr.data = new_data;
    arr.capacity = new_capacity;
}

//push value at the back
void push_back(Array& arr, int value){
    if(arr.size == arr.capacity){
        resize(arr);
    }

    arr.data[arr.size] = value;
    arr.size += 1; 
}

//insert at a position
void insert_at(Array& arr, size_t index, int value){
    if(arr.size == arr.capacity){
        resize(arr);
    }

    size_t count = arr.size - index;
    if(count > 0){
        my_memmove(arr.data + index + 1, arr.data + index , sizeof(int) * count);   //dst is src + 1; moving by count bytes
    }

    arr.data[index] = value;
    arr.size += 1;
}

void print(Array& arr){
    for (size_t i = 0; i < arr.size; ++i)
    {
        std::cout << arr.data[i] << " ";
    }
    std::cout<<"\n";
}

int main(){
    Array arr;
    init(arr);

    push_back(arr,10);
    push_back(arr,20);
    push_back(arr,30);
    push_back(arr,40);
    push_back(arr,50);

    print(arr);

    insert_at(arr,3,100);

    print(arr);

    destroy(arr);

    return 0;
}



