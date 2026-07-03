/* Exercise 3 — Specialization

  Write a generic to_string(T value) function template that converts any type to a std::string using a std::ostringstream. Then write full specializations for:
  - bool — returns "true" or "false" (not "1" or "0")
  - const char* — returns the string as-is, wrapped in quotes: "hello" → "\"hello\""

  Test all three paths:
  to_string(42)       // "42"
  to_string(true)     // "true"
  to_string("hello")  // "\"hello\""
  */

#include <iostream>
#include <sstream>

template<typename T>
std::string to_string(T value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Full specialization for bool
template<>
std::string to_string<bool>(bool value) {
    return value ? "true" : "false";
}

// Full specialization for const char*
template<>
std::string to_string<const char*>(const char* value) {
    return "\"" + std::string(value) + "\"";
}

int main() {
    std::cout << to_string(42) << '\n';
    std::cout << to_string(3.14) << '\n';
    std::cout << to_string(true) << '\n';
    std::cout << to_string(false) << '\n';
    std::cout << to_string("hello") << '\n';
}