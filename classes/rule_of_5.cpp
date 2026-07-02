/*
Coding Exercises

  Exercise 1 — Build a String class

  Write a String class from scratch. It must:
  - Store a heap-allocated null-terminated char* and its length
  - Constructor from const char* (allocate and copy) 
  - Destructor (free)
  - Deep copy constructor and copy assignment
  - Move constructor and move assignment
  - length(), c_str(), operator[] (with bounds check), print()

  No std::string. Use strlen, memcpy (or write your own).
*/

#include <iostream>

class String{
    char* data;
    size_t len;

    static char* allocate_and_copy(const char* s, size_t len) {
        char* buffer = new char[len + 1];
        memcpy(buffer, s, len);
        buffer[len] = '\0';
        return buffer;
    }

public:
    String() : data(new char[1]{'\0'}), len(0) {}

    String(const char* s){
        if(s == nullptr){
            len = 0;
            data = new char[1]{'\0'};
            return;
        }
        len = strlen(s);
        data = allocate_and_copy(s, len);
    }

    ~String() {
        delete[] data;
    }

    String(const String& other) : len(other.len){
        data = allocate_and_copy(other.data, other.len);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            char* new_data = allocate_and_copy(other.data, other.len);
            delete[] data;
            data = new_data;
            len = other.len;
        }
        return *this;
    }

    String(String&& other) noexcept : data(other.data), len(other.len){
        other.len = 0;
        other.data = nullptr;
    }

    String& operator=(String&& other) noexcept{
        if(this != &other){
            delete[] data;
            data = other.data;
            len = other.len;

            other.data = nullptr;
            other.len = 0;
        }
        return *this;
    }

    size_t length() const {
        return len;
    }
    
    const char* c_str() const {
        return data;
    }

    char& operator[](size_t index) {
        if (index >= len) {
            throw std::out_of_range("String::operator[] out of range");
        }
        return data[index];
    }

    const char& operator[](size_t index) const {
        if (index >= len) {
            throw std::out_of_range("String::operator[] out of range");
        }
        return data[index];
    }

    void print() const {
        std::cout << data << '\n';
    }

};

int main(){
    String a("hello");
    String b = a;          // copy
    String c = std::move(a); // move

    //a.print();               cause segfault
    b[0] = 'H';
    b.print();             
    
    std::cout << c.c_str() << "\n"; 
    c.print();                             //same as c.c_str()
    std::cout << c.length() << "\n";
}