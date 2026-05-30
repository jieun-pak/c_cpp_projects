#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	// Valid form creation
	try
	{
		Form f("Tax Return", 50, 25);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Form with invalid grade (too high)
	try
	{
		Form f("BadForm", 0, 10);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (grade 0): " << e.what() << std::endl;
	}

	// Form with invalid grade (too low)
	try
	{
		Form f("BadForm", 10, 151);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception (grade 151): " << e.what() << std::endl;
	}

	// Bureaucrat with high enough grade signs form
	try
	{
		Bureaucrat alice("Alice", 40);
		Form f("Pension", 50, 25);
		std::cout << alice << std::endl;
		std::cout << f << std::endl;
		alice.signForm(f);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Bureaucrat with grade too low to sign
	try
	{
		Bureaucrat bob("Bob", 100);
		Form f("Top Secret", 50, 25);
		std::cout << bob << std::endl;
		std::cout << f << std::endl;
		bob.signForm(f);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
