/*Exercise 2 — Implement memmove
Write my_memmove. The key test is the overlapping case — make sure it handles both directions correctly. */

#include <iostream>

void* my_memmove(void* dst, const void* src, size_t n){
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;

    if(d==s){
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

int main(){
    char a[] = "hello";
    char b[6] = {};
    my_memmove(b, a, 6);
    std::cout << b << "\n";   // hello
  
    // test 2: dst > src, overlapping — the dangerous case
    char buf[] = "ABCDEF";
    my_memmove(buf + 2, buf, 4);   // copy ABCD into position 2
    std::cout << buf << "\n";      // ABABCD

    // test 3: dst < src, overlapping
    char buf2[] = "ABCDEF";
    my_memmove(buf2, buf2 + 2, 4);  // copy CDEF into position 0
    std::cout << buf2 << "\n";
    
    return 0;
}