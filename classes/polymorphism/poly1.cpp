/*
Exercise 1 — Polymorphic Shape Renderer

  Build a system with a base class Shape (pure virtual area(), perimeter(), name()) and three derived classes: Circle, Rectangle, Triangle. Each stores its own dimensions.

  Write a function render_all(Shape** shapes, int n) that iterates the array and prints each shape's name, area, and perimeter through the base pointer. Create a mixed array of all three types and render it. Add
  constructor/destructor prints to verify correct cleanup when you delete each shape.
*/

#include <iostream>

class Shape{
public:
    Shape(){
        std::cout << "Shape constructor \n";
    }
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual std::string name() = 0;
    virtual ~Shape(){
        std::cout << "Shape destructor \n";
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r){
        std::cout << "Circle constructed\n";
    }

    double area() override{
        return 3.14 * radius * radius;
    }

    double perimeter() override{
        return 3.14 * 2 * radius;
    }

    std::string name() override{
        return "Circle";
    }

    ~Circle() override{
        std::cout << "Circle destructed\n";
    }
};

class Rectangle : public Shape {
private:
    double length, height;
public:
    Rectangle(double l, double h) : length(l), height(h){
        std::cout << "Rectangle constructed\n";
    }

    double area() override{
        return length * height;
    }

    double perimeter() override{
        return 2 * (length + height);
    }

    std::string name() override{
        return "Rectangle";
    }

    ~Rectangle() override{
        std::cout << "Rectangle destructed\n";
    }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h){
        std::cout << "Triangle constructed\n";
    }

    double area() override{
        return 0.5 * base * height;
    }

    double perimeter() override{
        return base + height + base;
    }

    std::string name() override{
        return "Triangle";
    }

    ~Triangle() override{
        std::cout << "Triangle destructed\n";
    }
};

void render_all(Shape** shapes, int n){
    for(int i = 0 ; i < n; i++){
        std::cout<< shapes[i]->name() <<'\n';
        std::cout<< shapes[i]->area() <<'\n';
        std::cout<< shapes[i]->perimeter() <<'\n';
    }
}

int main(){
    Shape* shapes[3] = {new Circle(5), new Rectangle(2,3), new Triangle(5,5)};
    render_all(shapes,3); 
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }
    return 0;
}

