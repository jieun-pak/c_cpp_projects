#include "Bureaucrat.hpp"

int main()
{
	std::cout << "\n===========[Part 1: Valid bureaucrat]===========" << std::endl;
	try
	{
		Bureaucrat b("Jinny", 1);
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

	std::cout << "\n===========[Part 2: Grade too high (0)]===========" << std::endl;
	try
	{
		Bureaucrat b("Habib", 0);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (grade 0): " << e.what() << std::endl;
	}

	std::cout << "\n===========[Part 3: Grade too low (151)]===========" << std::endl;
	try
	{
		Bureaucrat b("Min", 151);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (grade 151): " << e.what() << std::endl;
	}

	std::cout << "\n===========[Part 4: Increment past highest grade]===========" << std::endl;
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

	std::cout << "\n===========[Part 5: Decrement past lowest grade]===========" << std::endl;
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
