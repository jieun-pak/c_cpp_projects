#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base *generate(void)
{
	int r = rand() % 3;
	if (r == 0)
	{
		std::cout << "[generate] Created A" << std::endl;
		return new A();
	}
	if (r == 1)
	{
		std::cout << "[generate] Created B" << std::endl;
		return new B();
	}
	std::cout << "[generate] Created C" << std::endl;
	return new C();
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "identify(ptr): A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "identify(ptr): B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "identify(ptr): C" << std::endl;
	else
		std::cout << "identify(ptr): unknown" << std::endl;
}

void identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "identify(ref): A" << std::endl;
		return;
	}
	catch (std::exception &) {}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "identify(ref): B" << std::endl;
		return;
	}
	catch (std::exception &) {}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "identify(ref): C" << std::endl;
		return;
	}
	catch (std::exception &) {}
	std::cout << "identify(ref): unknown" << std::endl;
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	std::cout << "===========[5 random type identifications]===========" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "\n--- Round " << i + 1 << " ---" << std::endl;
		Base *obj = generate();
		identify(obj);
		identify(*obj);
		delete obj;
	}

	std::cout << "\n===========[Direct type tests]===========" << std::endl;

	Base *a = new A();
	Base *b = new B();
	Base *c = new C();

	std::cout << "\n[A pointer/reference]" << std::endl;
	identify(a);
	identify(*a);

	std::cout << "\n[B pointer/reference]" << std::endl;
	identify(b);
	identify(*b);

	std::cout << "\n[C pointer/reference]" << std::endl;
	identify(c);
	identify(*c);

	delete a;
	delete b;
	delete c;

	return 0;
}
