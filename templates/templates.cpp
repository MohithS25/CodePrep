#include <iostream>

template <typename T>
T my_max(T a, T b){
    return a > b ? a : b;
}

 template<typename T, typename U> 
  void print_pair(T first, U second) {
      std::cout << first << ", " << second << '\n';
  }

int main(){
    int    x = my_max(3, 5);        // compiler generates max<int>
    double y = my_max(3.14, 2.71);  // compiler generates max<double>
    std::string s = my_max(std::string("a"), std::string("b")); // max<string>
    std::cout << x <<'\n';
    std::cout << y <<'\n';
    std::cout << s <<'\n';

    double p = my_max<double>(3, 5.0);


    print_pair(42, "hello");        // T=int, U=const char*
    print_pair(3.14, true);
}