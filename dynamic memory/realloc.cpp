/* Exercise 3 — Implement a simple realloc

  Using your my_memcpy, implement a simplified my_realloc. It receives a pointer to an existing heap allocation, the old size, and the new (larger) size. It should allocate a new block, copy the old data, free the
  old block, and return the new pointer. This is exactly what the real realloc does. */


#include <iostream>

void* my_memcpy(void* dst, const void* src, size_t n){
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;

    for(int i = 0; i<n; i++){
        d[i] = s[i];
    }
    return dst;
}

void* my_realloc(void* arr, size_t old_size, size_t new_size){
    void* p = malloc(new_size);
    my_memcpy(p,arr,old_size);
    free(arr);
    return p;
}

int main(){
    int* arr = (int*)malloc(3 * sizeof(int));                        //keeping malloc consistent with my_realloc
    arr[0]=10; arr[1]=20; arr[2]=30;
    arr = (int*)my_realloc(arr, 3 * sizeof(int), 6 * sizeof(int));
    for (int i = 3; i < 6; i++){ 
        arr[i] = 0;        //adding zeroes to extra elements
    }
    for (int i = 0; i < 6; i++){
        std::cout << arr[i] << " ";  // 10 20 30 0 0 
    }    
    free(arr);
    return 0;
}


/*. //same thing with new and delete
void* my_realloc(void* ptr, size_t old_size, size_t new_size) {
      void* p = ::operator new(new_size);   // raw allocation, like malloc but C++
      my_memcpy(p, ptr, old_size);
      ::operator delete(ptr);               // raw free, matches ::operator new
      return p;
  }

  int main() {
      int* arr = (int*)::operator new(3 * sizeof(int));
      arr[0]=10; arr[1]=20; arr[2]=30;
  
      arr = (int*)my_realloc(arr, 3 * sizeof(int), 6 * sizeof(int));
      for (int i = 3; i < 6; i++) arr[i] = 0;
      for (int i = 0; i < 6; i++) std::cout << arr[i] << " ";
  
      ::operator delete(arr);   // matches ::operator new
  }
*/