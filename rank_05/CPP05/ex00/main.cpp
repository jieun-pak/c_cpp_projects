#include "Bureaucrat.hpp"

int main()
{
	// Valid bureaucrat
	try
	{
		Bureaucrat b("Alice", 1);
		std::cout << b << std::endl;
		b.decrementGrade();
		std::cout << b << std::endl;
		b.incrementGrade();
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Grade too high (0)
	try
	{
		Bureaucrat b("Bob", 0);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (grade 0): " << e.what() << std::endl;
	}

	// Grade too low (151)
	try
	{
		Bureaucrat b("Carol", 151);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (grade 151): " << e.what() << std::endl;
	}

	// Increment past highest grade
	try
	{
		Bureaucrat b("Dave", 1);
		std::cout << b << std::endl;
		b.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (increment from 1): " << e.what() << std::endl;
	}

	// Decrement past lowest grade
	try
	{
		Bureaucrat b("Eve", 150);
		std::cout << b << std::endl;
		b.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (decrement from 150): " << e.what() << std::endl;
	}

	return 0;
}
