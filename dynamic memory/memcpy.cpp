/* Coding Exercises
  Exercise 1 — Implement memcpy
  Write my_memcpy from scratch. Do not use any standard library memory functions inside it. */

#include <iostream>

void* my_memcpy(void* dst, const void* src, size_t n){
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;
    for(size_t i=0 ; i < n; i++){
        d[i] = s[i];
    }
    return dst;
}

int main(){
    char src[] = "hello";
    char dst[] = {"mohith"};
    std::cout << dst << "\n";
    my_memcpy(dst, src, 6);
    std::cout << dst << "\n";

    int nums[]={10,20,30,40};
    int arr[4] = {};
    my_memcpy(arr, nums, 4 * sizeof(int));
    for(int i = 0; i < 4; i++){
        std::cout << arr[i] << " ";
    }
    return 0;
}