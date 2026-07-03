/*Exercise 1 — Generic Stack<T>

  Write a class template Stack<T> from scratch. It must support:
  - push(T value) — add to top
  - pop() — remove from top (throw std::underflow_error if empty)
  - top() — return reference to top element (const and non-const versions)
  - empty() — true if no elements
  - size() — number of elements
  
  Use a heap-allocated array internally (like your dynamic Array from earlier — not std::vector). Handle growth when capacity is exceeded. Apply the Rule of Five correctly.

*/


#include <iostream>

template <typename T>
class Stack {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void grow() {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[new_capacity];

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Stack() : data_(nullptr), size_(0), capacity_(0) {}

    ~Stack() {
        delete[] data_;
    }

    Stack(const Stack& other)
        : data_(other.capacity_ ? new T[other.capacity_] : nullptr),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            T* new_data = other.capacity_ ? new T[other.capacity_] : nullptr;
            for (std::size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }

            delete[] data_;
            data_ = new_data;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    Stack(Stack&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    void push(T value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_++] = std::move(value);
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Stack::pop: empty stack");
        }
        --size_;
    }

    T& top() {
        if (empty()) {
            throw std::underflow_error("Stack::top: empty stack");
        }
        return data_[size_ - 1];
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack::top: empty stack");
        }
        return data_[size_ - 1];
    }

    bool empty() const {
        return size_ == 0;
    }

    std::size_t size() const {
        return size_;
    }
};

int main() {
    Stack<std::string> s;

    s.push("one");
    s.push("two");
    s.push("three");

    std::cout << s.top() << '\n'; // three
    s.pop();
    std::cout << s.top() << '\n'; // two
    std::cout << s.size() << '\n'; // 2

    Stack<std::string> copy = s;   // copy constructor
    Stack<std::string> moved = std::move(s); // move constructor

    std::cout << copy.top() << '\n';
    moved.pop();
    moved.pop();
    std::cout << moved.empty() << '\n';
    moved.push("four");
    std::cout << moved.top() << '\n';
}