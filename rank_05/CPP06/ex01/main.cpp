#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
	Data original;
	original.name = "Jieun";
	original.value = 42;
	original.score = 9.8;

	std::cout << "===========[Original Data]===========" << std::endl;
	std::cout << "Address  : " << &original << std::endl;
	std::cout << "name     : " << original.name << std::endl;
	std::cout << "value    : " << original.value << std::endl;
	std::cout << "score    : " << original.score << std::endl;

	uintptr_t raw = Serializer::serialize(&original);

	std::cout << "\n===========[Serialized]===========" << std::endl;
	std::cout << "uintptr_t: " << raw << std::endl;

	Data *recovered = Serializer::deserialize(raw);

	std::cout << "\n===========[Deserialized Data]===========" << std::endl;
	std::cout << "Address  : " << recovered << std::endl;
	std::cout << "name     : " << recovered->name << std::endl;
	std::cout << "value    : " << recovered->value << std::endl;
	std::cout << "score    : " << recovered->score << std::endl;

	std::cout << "\n===========[Pointer Comparison]===========" << std::endl;
	if (recovered == &original)
		std::cout << "PASS: recovered pointer matches original address" << std::endl;
	else
		std::cout << "FAIL: pointers do not match" << std::endl;

	return 0;
}
