/*Exercise 1 — Implement my_unique_ptr

  Write a complete my_unique_ptr<T> from scratch. It must support:
  - Constructor, destructor (calls delete)
  - Deleted copy constructor and copy assignment
  - Move constructor and move assignment
  - operator*, operator->, get(), operator bool
  - reset() and release()

  Test it with an int and a small struct. Verify ownership transfers correctly with move.
*/

#include <iostream>

template <typename T>
class my_unique_ptr{
    T* ptr;
    public:
        explicit my_unique_ptr(T* p = nullptr) : ptr(p){}         //constructor

        ~my_unique_ptr(){
            delete ptr;
        }

        my_unique_ptr(const my_unique_ptr&) = delete;
        my_unique_ptr& operator=(const my_unique_ptr&) = delete;
        
        my_unique_ptr(my_unique_ptr&& other) : ptr(other.ptr) {
            other.ptr = nullptr;
        }

        my_unique_ptr& operator=(my_unique_ptr&& other) {
            if(this != &other){
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }
        T* get() const { return ptr; }
        explicit operator bool() const {
            return ptr!=nullptr;
        }

        T* release(){
            T* tmp = ptr;
            ptr = nullptr;
            return tmp;
        }

        void reset(T* p = nullptr){
            delete ptr;
            ptr = p;
        }
};

struct Point
{
    int x;
    int y;

    void print() const
    {
        std::cout << "Point(" << x << ", " << y << ")\n";
    }
};

int main(){
    
    my_unique_ptr<int> p1(new int(42));
    std::cout << "p1 value = " << *p1 << "\n";
    std::cout << "p1 owns? " << bool(p1) << "\n";

    my_unique_ptr<int> p2 = std::move(p1);
    std::cout << "After move:\n";
    std::cout << "p1 owns? " << bool(p1) << "\n";
    std::cout << "p2 owns? " << bool(p2) << "\n";
    std::cout << "p2 value = " << *p2 << "\n";

    my_unique_ptr<Point> q1(new Point{3, 7});
    std::cout << "q1 at " << q1.get() << " -> ";
    q1->print();

    my_unique_ptr<Point> q2(new Point{10, 20});
    std::cout << "q2 before move at " << q2.get() << " -> ";
    q2->print();

    q2 = std::move(q1);

    std::cout << "After move assignment:\n";
    std::cout << "q1 owns? " << bool(q1) << "\n";
    std::cout << "q2 owns? " << bool(q2) << "\n";
    std::cout << "q2 now at " << q2.get() << " -> ";
    q2->print();

    return 0;
}