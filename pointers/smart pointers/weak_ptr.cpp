/*Exercise 3 — Fix the Cycle

  This code leaks memory. Find the cycle, explain why it leaks, and fix it using weak_ptr:

  #include <memory>   
  #include <iostream>

  struct Owner {
      std::shared_ptr<Pet> pet;
      ~Owner() { std::cout << "Owner destroyed\n"; }
  };
  
  struct Pet {
      std::shared_ptr<Owner> owner;
      ~Pet() { std::cout << "Pet destroyed\n"; }
  };

  int main() { 
      auto owner = std::make_shared<Owner>();
      auto pet   = std::make_shared<Pet>();
      owner->pet   = pet;
      pet->owner   = owner;
  }
*/

  #include <memory>   
  #include <iostream>

  struct Pet;

  struct Owner {
      std::shared_ptr<Pet> pet;
      ~Owner() { std::cout << "Owner destroyed\n"; }
  };
  
  struct Pet {
      std::weak_ptr<Owner> owner;
      ~Pet() { std::cout << "Pet destroyed\n"; }
  };

  int main() { 
      auto owner = std::make_shared<Owner>();
      auto pet   = std::make_shared<Pet>();
      owner->pet   = pet;
      pet->owner   = owner;
  }
