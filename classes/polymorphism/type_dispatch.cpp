/*
Write an Animal base with virtual void speak(). Derive Dog (adds void fetch()) and Cat (adds void purr()). Create an array of Animal* with a mix of Dogs and Cats.

  Write a function process(Animal* a) that:
  - Always calls speak()
  - If it's a Dog, also calls fetch()
  - If it's a Cat, also calls purr()

  Use dynamic_cast for the type checks. Then write a second version that achieves the same result WITHOUT dynamic_cast — by adding virtual functions to the base instead. Compare the two designs and write a comment
  explaining which is better and why.
*/


#include <iostream>

struct Animal {
    virtual ~Animal() = default;
    virtual void speak() { std::cout << "...\n"; }
};

struct Dog : Animal {
    void speak() override { std::cout << "Woof!\n"; }
    void fetch() { std::cout << "Dog fetches the ball.\n"; }
};

struct Cat : Animal {
    void speak() override { std::cout << "Meow!\n"; }
    void purr() { std::cout << "Cat purrs.\n"; }
};

// Version 1: uses dynamic_cast
void process(Animal* a) {
    a->speak();

    if (Dog* d = dynamic_cast<Dog*>(a)) {
        d->fetch();
    } else if (Cat* c = dynamic_cast<Cat*>(a)) {
        c->purr();
    }
}

// Version 2: no dynamic_cast, just virtual functions in the base
struct Animal2 {
    virtual ~Animal2() = default;
    virtual void speak() { std::cout << "...\n"; }

    // Default no-op hooks
    virtual void fetch() {}
    virtual void purr() {}
};

struct Dog2 : Animal2 {
    void speak() override { std::cout << "Woof!\n"; }
    void fetch() override { std::cout << "Dog fetches the ball.\n"; }
};

struct Cat2 : Animal2 {
    void speak() override { std::cout << "Meow!\n"; }
    void purr() override { std::cout << "Cat purrs.\n"; }
};

void process2(Animal2* a) {
    a->speak();
    a->fetch();
    a->purr();
}

int main(){
    Animal* zoo[] = { new Dog(), new Cat(), new Dog(), new Cat() };

    for (Animal* a : zoo) {
        process(a);
        std::cout << '\n';
    }

    for (Animal* a : zoo) {
        delete a;
    }

    std::cout << "=== virtual-function version ===\n";

    Animal2* zoo2[] = { new Dog2(), new Cat2(), new Dog2(), new Cat2() };

    for (Animal2* a : zoo2) {
        process2(a);
        std::cout << '\n';
    }

    for (Animal2* a : zoo2) {
        delete a;
    }

    return 0;
}

 // Version 1 (dynamic_cast) is more honest but fragile.
  // It's honest: the base class isn't polluted with Dog/Cat-specific methods.
  // It's fragile: add a new animal type (Parrot) and process() must be updated everywhere.
  // Scales badly as O(types) code in the dispatch function.
  //
  // Version 2 (virtual functions in base) has the opposite tradeoffs.
  // fetch() and purr() in Animal2 make no semantic sense — a Cat can't fetch.
  // No-op defaults are a design smell: they lie about what Animal2 can do.
  // But it scales well — new animal types just override what's relevant.
  //
  // The real solution is the Visitor pattern or rethinking the hierarchy:
  // if each animal only needs to "do its thing", a single virtual do_special()
  // in the base class is clean. If you genuinely need type-specific behavior
  // at the call site, that's often a sign the design needs revisiting.
  //
  // Between these two: prefer virtual functions if the behavior logically belongs
  // in the base contract. Use dynamic_cast only when interacting with types you
  // don't control or when the cast is genuinely exceptional.

