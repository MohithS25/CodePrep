/*Coding Exercises
Exercise 1 — Arena from Scratch
Implement the arena allocator completely from scratch without looking back. Then use it to allocate and use several different types (int, double, a small struct), reset it, and allocate again. Verify you can
reuse the arena after reset.
  */


#include <iostream>

struct Arena{
    unsigned char* buffer;
    size_t capacity;
    size_t offset;
};

void init(Arena& a, size_t capacity){
    a.buffer = new unsigned char[capacity];
    a.capacity = capacity;
    a.offset = 0;
}

void* arena_alloc(Arena& a,size_t size){
    size = (size + 7) & ~7;
    if(a.offset + size > a.capacity){
        return nullptr;
    }
    void* ptr = a.buffer + a.offset;
    a.offset += size;
    return ptr;
}

void reset_arena(Arena& a){
    a.offset = 0;
}

void destroy(Arena& a){
    delete[] a.buffer;
    a.buffer = nullptr;
    a.capacity = 0;
    a.offset = 0;
}

int main(){
    Arena a;
    init(a,64);

    int* pi = (int*)arena_alloc(a,sizeof(int));
    double* pd = (double*)arena_alloc(a,sizeof(double));
    *pi = 42;
    *pd = 3.14159;

    std::cout << "Before free: " << "int: " << *pi <<" Address: " << (void*)pi <<"\n"; 
    std::cout << "Before free: " << "double: " << *pd <<" Address: " << (void*)pd <<"\n"; 

    void* old_pi = pi;
    void* old_pd = pd;

    reset_arena(a);
    int* pi1 = (int*)arena_alloc(a,sizeof(int));
    double* pd1 = (double*)arena_alloc(a,sizeof(double));
    *pi1 = 32;
    *pd1 = 5.14159;

    std::cout << "After reset: " << "int: " << *pi1 <<" Address: " << (void*)pi1 <<"\n"; 
    std::cout << "After reset: " << "double: " << *pd1 <<" Address: " << (void*)pd1 <<"\n"; 

    std::cout << (old_pi == (void*)pi1 ? "Same address reused" : "Different address") << "\n";


    destroy(a);

    return 0;

}