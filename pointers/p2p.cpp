#include <iostream>

int main(){
    int x =10;
    int* p =&x;
    int** pp = &p;
    *pp = nullptr;
    std::cout<<p<<"\t"<<x<<std::endl;
    int* b = p;

    std::cout<<*b<<"\t"<<*p<<"\t"<<**pp<<std::endl;
    return 0;
}