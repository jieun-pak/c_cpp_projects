#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
	std::cout << "=== Subject Test: Delete as Animal ===" << std::endl;
	const Animal obj;
	const Animal* thisAlsoFails = new Animal();
	(void)thisAlsoFails;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;
	delete i;

	std::cout << "\n=== Array of Animals Test ===" << std::endl;
	const int arraySize = 4;
	Animal* animals[arraySize];

	for (int idx = 0; idx < arraySize / 2; idx++) {
		animals[idx] = new Dog();
	}
	std::cout << "----" << std::endl;

	for (int idx = arraySize / 2; idx < arraySize; idx++) {
		animals[idx] = new Cat();
	}
	std::cout << "----" << std::endl;

	for (int idx = 0; idx < arraySize; idx++) {
		delete animals[idx];
	}

	std::cout << "\n=== Deep Copy Test ===" << std::endl;
	Dog dog1;
	dog1.getBrain()->setIdea(0, "I love bones");
	Dog dog2 = dog1;

	std::cout << "Dog1 Brain address: " << dog1.getBrain() << std::endl;
	std::cout << "Dog2 Brain address: " << dog2.getBrain() << std::endl;

	if (dog1.getBrain() != dog2.getBrain()) {
		std::cout << "Result> Different addresses (Deep Copy)" << std::endl;
	} else {
		std::cout << "Result> Same address (Shallow Copy)" << std::endl;
	}
	std::cout << "\n=== Assignment Operator Test ===" << std::endl;
	Cat cat1;
	std::cout << "----" << std::endl;

	Cat cat2;
	std::cout << "----" << std::endl;

	cat2 = cat1;
	std::cout << "====== Assignment complete >_< =======" << std::endl;

	return 0;
}
