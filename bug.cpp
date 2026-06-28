 #include <iostream>

  int divide(int a, int b) {
      return a / b;
  }

  int main() {
      int x = 10;
      int y = 0;
      std::cout << divide(x, y) << "\n";   // crash — division by zero
      return 0;
  }