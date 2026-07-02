/*
Exercise 2 — Shape hierarchy

  Write an abstract Shape base class with pure virtual area() and perimeter(). Derive Circle and Rectangle from it. Each stores its own dimensions.

  Then write:
  void print_info(Shape* s);   // prints area and perimeter through base pointer
  
  Call it with both a Circle and a Rectangle. Add print statements to each constructor and destructor to verify correct construction and destruction order.

*/

#include <iostream>

class Shape{

public:
    Shape() {
        std::cout << "Shape constructor \n";
    }
    
    virtual double area() = 0;
    virtual double perimeter() = 0;

    virtual ~Shape(){
        std::cout << "Shape destructor called \n";
    }

};

class Rectangle : public Shape {
    double length;
    double width;
public:
    Rectangle(double l, double w) : length(l), width(w) {
        std::cout << "Rectangle constructor called \n";
    }

    ~Rectangle() override {
        std::cout << "Rectangle destructor called \n";
    }

    double area() override {
        return length * width;
    }

    double perimeter() override {
        return 2 * (length + width); 
    }
};

class Circle : public Shape {
    double radius;

public:
    Circle(double r) : radius(r){
        std::cout << "Circle constructor called \n";
    }

    ~Circle() override{
        std::cout << "Circle destructor called \n";
    }

    double area() override {
        return radius * radius * 3.14;
    }

    double perimeter() override {
        return 2 * 3.14 * radius;
    }
};

void print_info(Shape* s){
    std::cout << "Area: " << s->area() << '\n';
    std::cout << "Perimeter: " << s->perimeter() << '\n';
}

int main(){
    Circle c(5);
    Rectangle r(4, 6);

    print_info(&c);

    print_info(&r);

    return 0;
}