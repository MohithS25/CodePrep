/*
Write this exact scenario, run it, observe the output, then fix it:

  struct Animal {
      virtual void speak() { std::cout << "...\n"; }
  };
  struct Dog : Animal {
      void speak() override { std::cout << "Woof!\n"; }
  };

  void make_sound(Animal a) { a.speak(); }   // takes by value

  int main() { 
      Dog d;
      make_sound(d);   // what do you expect vs what happens?   -> calls animal speak since we are passing by copy dog object to an animal object
  }
  
  After observing slicing, fix make_sound so it correctly calls Dog::speak. Then write a second version that triggers slicing through a std::vector — store Dogs in a vector<Animal> (by value) and observe what
  happens when you call speak() on each element.
*/

#include <iostream>

struct Animal {
    virtual void speak() { std::cout << "...\n"; }
};
struct Dog : Animal {
    void speak() override { std::cout << "Woof!\n"; }
};

void make_sound(Animal& a) { a.speak(); }

int main() { 
    Dog d;
    make_sound(d);   

    //pass by value
    std::vector<Animal> zoo;
    zoo.push_back(Dog{});
    zoo.push_back(Dog{});
    for (auto& a : zoo) {
        a.speak();
    }

    //using pointers
    std::vector<std::unique_ptr<Animal>> zoo2;
    zoo2.push_back(std::make_unique<Dog>());
    zoo2.push_back(std::make_unique<Dog>());

    for (auto& a : zoo2) {
        a->speak();
    }
}