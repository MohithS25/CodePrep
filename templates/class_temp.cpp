#include <iostream>

template<typename T>
  class Box {
      T value; 
  public:
      explicit Box(T v) : value(v) {}
      T&       get()       { return value; }
      const T& get() const { return value; }
      void     set(T v)    { value = v; }
  };

int main(){
  Box<int>         a(42);
  Box<double>      b(3.14);
  Box<std::string> c("hello");

  std::cout << a.get() <<'\n';
  a.set(50);
  std::cout << a.get() <<'\n';
    
    std::cout << c.get() <<'\n';

}