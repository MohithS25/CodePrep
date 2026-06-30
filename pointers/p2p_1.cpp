#include <iostream>

void initialize(int** pp, int value) {
      *pp = new int(value);
  }
  
  int main() {
      int* p = nullptr;
      initialize(&p, 42);
      std::cout << *p << "\n";   // should print 42
      delete p;
  }
