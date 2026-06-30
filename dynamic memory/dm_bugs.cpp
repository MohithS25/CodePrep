#include <iostream>

  int* make_data(int n) {
      int* arr = new int[n];
      for (int i = 0; i < n; i++) arr[i] = i * 2;
      return arr;
  }
  
  void process(int* data, int size) {
      for (int i = 0; i < size; i++) {   // note: <= size makes it take array out of bounds, prints some random value
          std::cout << data[i] << "\n";
      }
      //delete[] data;                        // double delete 
  }

  int main() {
      int* d = make_data(4);
      process(d, 4);
      std::cout << d[0] << "\n";            //since data was deleted this will return some random value
      delete[] d;                           
  }