# deep copy (ex01)
⏺ Deep Copy vs Shallow Copy Explained

  The Problem: Dog has a Brain* pointer

  In Dog.hpp:9, Brain* brain is a pointer. This is where the issue arises.

  ---
  Shallow Copy (BAD)

  If you DON'T implement proper copy constructor and assignment operator:

  // ❌ SHALLOW COPY (what happens by default)
  Dog::Dog(const Dog& other) : Animal(other) {
      brain = other.brain;  // Just copies the POINTER ADDRESS
  }

  What happens:
  Original Dog:           Copied Dog:
  +--------+              +--------+
  | brain  |--\           | brain  |--\
  +--------+   \          +--------+   \
                \                       \
                 +---> [Same Brain Object] <---+
                       (0x1234)

  Problems:
  1. Both dogs share the SAME Brain - modifying one affects the other
  2. Double delete - when one dog dies and deletes the brain, the other dog's brain pointer becomes invalid (dangling pointer)
  3. When the second dog tries to delete → CRASH or undefined behavior

  ---
  Deep Copy (GOOD) ✅

  Your implementation at Dog.cpp:9-11:

  Dog::Dog(const Dog& other) : Animal(other) {
      brain = new Brain(*other.brain);  // Creates NEW Brain, copies content
  }

  What happens:
  Original Dog:           Copied Dog:
  +--------+              +--------+
  | brain  |----> [Brain] | brain  |----> [Brain]
  +--------+      0x1234  +--------+      0x5678
                  ↑                         ↑
             "good dog"                "good dog"
             (same content,           (different memory)
              different objects)

  Benefits:
  1. Each dog has its OWN Brain - independent memory
  2. Modifying one doesn't affect the other (line 52-54 in main.cpp tests this)
  3. Safe destruction - each dog deletes its own brain

  ---
  Your Implementation Analysis

  Copy Constructor (Dog.cpp:9-11)

  Dog::Dog(const Dog& other) : Animal(other) {
      brain = new Brain(*other.brain);  // ✅ Allocates NEW Brain, copies data
  }

  Assignment Operator (Dog.cpp:14-22)

  Dog& Dog::operator=(const Dog& other) {
      if (this != &other) {
          Animal::operator=(other);
          delete brain;                  // ✅ Delete old brain first!
          brain = new Brain(*other.brain);  // ✅ Allocate new one
      }
      return *this;
  }

  Critical step at line 18: delete brain - prevents memory leak by freeing the old brain before allocating a new one.

  ---
  Visual Test from main.cpp:47-48

  std::cout << "Brain addresses different? "
            << (basic.getBrain() != tmp.getBrain() ? "YES (deep copy)" : "NO (shallow copy)")

  This checks if the brain pointers point to different addresses:
  - Different addresses = Deep copy ✅
  - Same address = Shallow copy ❌

  ---
  The Danger Scenario (Shallow Copy)

  {
      Dog dog1;
      dog1.getBrain()->setIdea(0, "original");

      Dog dog2 = dog1;  // Shallow copy

      dog2.getBrain()->setIdea(0, "CHANGED");
      std::cout << dog1.getBrain()->getIdea(0);  // Prints "CHANGED" ⚠️

  }  // dog2 destroyed, deletes brain
     // dog1's brain pointer now points to deleted memory → CRASH when dog1 destroys

  Your deep copy implementation prevents this! Each dog manages its own brain independently.


  ## ex02

   Exercise 02 Subject Requirements

  The Problem Statement

  From the subject:
  "Creating Animal objects doesn't make sense after all. It's true, they make no sound! To avoid any possible mistakes, the default Animal class should not be instantiable."

  The task is to prevent direct instantiation of the Animal class while keeping everything else working exactly as before.

  ---
  Core Concept: Abstract Classes

  What is an Abstract Class?

  An abstract class in C++ is a class that:
  1. Cannot be instantiated directly (you can't do Animal a; or new Animal())
  2. Must be inherited to be useful
  3. Contains at least one pure virtual function

  Pure Virtual Function

  A pure virtual function is declared with = 0:

  class Animal {
  public:
      virtual void makeSound() const = 0;  // Pure virtual function
      //                             ^^^^
      //                        This makes it pure virtual
  };

  ---
  Implementation in ex02/Animal.hpp

  Looking at your implementation:

  class Animal {
  protected:
      std::string type;

  public:
      Animal();
      Animal(const Animal& other);
      Animal& operator=(const Animal& other);
      virtual ~Animal();

      virtual void makeSound() const = 0;  // ← Pure virtual (abstract)
      std::string getType() const;
  };

  Key Change from ex01:
  - ex01: virtual void makeSound() const; (can be instantiated)
  - ex02: virtual void makeSound() const = 0; (cannot be instantiated)

  ---
  What This Achieves

  1. Prevents Nonsensical Objects

  // ❌ This will NOT compile in ex02:
  Animal generic;           // Error: cannot instantiate abstract class
  Animal* ptr = new Animal(); // Error: cannot instantiate abstract class

  // ✅ This still works:
  Animal* dog = new Dog();  // OK - Dog is concrete
  Animal* cat = new Cat();  // OK - Cat is concrete

  2. Enforces Contract

  The abstract class says: "Any derived class MUST implement makeSound()"

  class Dog : public Animal {
  public:
      void makeSound() const {  // MUST implement this
          std::cout << "Woof! Woof!" << std::endl;
      }
  };

  If Dog didn't implement makeSound(), Dog would also be abstract and couldn't be instantiated.

  3. Polymorphism Still Works

  Even though Animal can't be instantiated, polymorphism works perfectly:

  Animal* animals[4];
  animals[0] = new Dog();  // Polymorphic pointer
  animals[1] = new Cat();

  for (int i = 0; i < 2; i++) {
      animals[i]->makeSound();  // Calls Dog/Cat version
      delete animals[i];         // Proper cleanup via virtual destructor
  }

  ---
  Why Does This Make Sense?

  Philosophical Reason

  // What sound does a generic "Animal" make? 
  // We don't know! Only specific animals have sounds.

  Animal a;
  a.makeSound();  // ??? What should this print?

  // By making Animal abstract, we prevent this confusion

  Design Pattern: Interface

  Abstract classes serve as interfaces or contracts:

  // Animal says: "I define WHAT needs to be done"
  class Animal {
      virtual void makeSound() const = 0;  // You MUST make a sound
  };

  // Dog says: "I define HOW to do it"
  class Dog : public Animal {
      void makeSound() const {
          std::cout << "Woof!" << std::endl;  // Here's HOW
      }
  };

  ---
  Comparison: ex01 vs ex02

  | Aspect        | ex01 (Concrete Animal)     | ex02 (Abstract Animal)           |
  |---------------|----------------------------|----------------------------------|
  | Instantiation | new Animal() ✅ works      | new Animal() ❌ error            |
  | makeSound()   | Has implementation         | Pure virtual (no implementation) |
  | Purpose       | Can create generic animals | Forces specific animal types     |
  | Polymorphism  | ✅ Works                   | ✅ Works                         |
  | Inheritance   | Optional                   | Required to use                  |

  ---
  Testing the Abstract Class

  Your ex02/main.cpp demonstrates this works correctly:

  // This would fail to compile if uncommented:
  // Animal generic;  // Error!

  // But this works (polymorphic usage):
  const Animal* j = new Dog();
  const Animal* i = new Cat();

  j->makeSound();  // "Woof! Woof!"
  i->makeSound();  // "Meow! Meow!"

  delete j;  // Proper cleanup
  delete i;

  ---
  Key Takeaways

  1. Abstract Class = At least one pure virtual function (= 0)
  2. Cannot instantiate abstract classes directly
  3. Must inherit and implement all pure virtual functions
  4. Still allows polymorphism through pointers/references
  5. Enforces design - prevents creating meaningless objects
  6. Virtual destructor is still essential for proper cleanup

  This concept is fundamental to object-oriented design and creates robust, logical class hierarchies where only concrete, meaningful objects can exist.
