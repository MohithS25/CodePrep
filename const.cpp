#include <iostream>

template <typename T>
void printPointerInfo(const std::string& label, const T* ptr) {
if (ptr == nullptr) {
std::cout << label << ": [Null Pointer]" << std::endl;
return;
}
// ptr -> The address stored in the pointer
// *ptr -> The value being pointed to (works for int, string, double, etc.)
// &ptr -> The address of the pointer variable itself
std::cout << label << " -> Stored Addr: " << ptr
<< " Dereferenced Val: " << *ptr
<< " Pointer's Own Addr: " << &ptr << std::endl;
}


int main(){
    int x = 10;
    const int* p = &x;
    printPointerInfo("p",p);
    
    x = 99;       // this works because the variable is not declared as const so we can directly modify it's value

    printPointerInfo("p",p);
    
    // *p = 100;   -> this doesn't work because the compiler is told that p will only read the data but won't modify it with const

    const int y = 20;
    // y = 100;   -> throws error
    
    const int& p1 = y;
    printPointerInfo("p1",&p1);
    printPointerInfo("y",&y);

    std::string s1 = "hello";

    const std::string* const p2 = &s1;
    printPointerInfo("p2",p2);

    return 0;

}