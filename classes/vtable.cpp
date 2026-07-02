/*
Exercise 3 — Mini vtable inspection

  Write a class Base with two virtual functions foo() and bar(), and a derived class Derived that overrides only foo(). Then:

  Base* b = new Derived();

  Print the addresses of b->foo and b->bar by extracting the vptr and reading function pointers directly from it. You'll need to cast the vptr:

  void** vptr = *(void***)b;
  // vptr[0] is the first virtual function's address
  // vptr[1] is the second
  
  Then print and compare the function addresses against &Base::foo, &Base::bar, &Derived::foo directly. You'll see that vptr[0] matches Derived::foo and vptr[1] matches Base::bar. This is the vtable working in
  practice.
*/

#include <iostream>

class Base {
public:

    virtual void foo(){
        std::cout << "Base::foo\n";
    };
    virtual void bar(){
        std::cout << "Base::bar\n";
    };
};

class Derived : public Base {
public:
    void foo() override {
        std::cout << "Derived::foo\n";
    }
};

int main(){
    Base* b = new Derived();
    
    void** vptr = *(void***)b;

    std::cout << "vptr[0] = " << vptr[0] << '\n';
    std::cout << "vptr[1] = " << vptr[1] << '\n';

    using FnPtr = void(*)();
    FnPtr vfoo = (FnPtr)vptr[0];           // vfoo holds Derived::foo's address 
    FnPtr vbar = (FnPtr)vptr[1];           // vbar holds Base::bar's address   

    std::cout << (void*)vfoo << '\n';
    std::cout << (void*)vbar << '\n';


    b->foo();
    b->bar();

    return 0;
}

