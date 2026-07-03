/*Exercise 2 — Generic Array Algorithms

  Write these three function templates that work on C-style arrays of any type, using a non-type template parameter for the size:

  template<typename T, int N>   
  T array_min(T (&arr)[N]);    // minimum element

  template<typename T, int N>   
  T array_max(T (&arr)[N]);    // maximum element

  template<typename T, int N>
  void array_reverse(T (&arr)[N]);  // reverse in place
  
  T (&arr)[N] is a reference to an array of N elements of type T — this lets the compiler deduce both T and N from the argument, so you can call array_min(my_array) without specifying anything explicitly.

  Test with int, double, and std::string arrays.
  */

#include <iostream>
#include <string>

template<typename T, int N>
T array_min(T (&arr)[N]) {
    T min = arr[0];

    for (int i = 1; i < N; i++) {
        if (arr[i] < min)
            min = arr[i];
    }

    return min;
}

template<typename T, int N>
T array_max(T (&arr)[N]) {
    T max = arr[0];

    for (int i = 1; i < N; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

template<typename T, int N>
void array_reverse(T (&arr)[N]) {
    int left = 0;
    int right = N - 1;

    while (left < right) {
        T temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }
}

template<typename T, int N>
void sort_array(T (&arr)[N]) {
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template<typename T, int N>
void print_array(T (&arr)[N]) {
    for (int i = 0; i < N; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

int main() {

    int a[] = {5, 2, 8, 1, 4};
    double b[] = {3.5, 1.2, 7.8, 0.9};
    std::string c[] = {"pear", "apple", "orange", "banana"};

    std::cout << "Integer Array\n";
    print_array(a);
    std::cout << "Min: " << array_min(a) << '\n';
    std::cout << "Max: " << array_max(a) << '\n';
    array_reverse(a);
    print_array(a);
    sort_array(a);
    print_array(a);

    std::cout << "\nDouble Array\n";
    print_array(b);
    std::cout << "Min: " << array_min(b) << '\n';
    std::cout << "Max: " << array_max(b) << '\n';
    array_reverse(b);
    print_array(b);
    sort_array(b);
    print_array(b);

    std::cout << "\nString Array\n";
    print_array(c);
    std::cout << "Min: " << array_min(c) << '\n';
    std::cout << "Max: " << array_max(c) << '\n';
    array_reverse(c);
    print_array(c);
}