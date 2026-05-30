#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));

	Intern someRandomIntern;
	AForm *form;

	// From the subject example
	std::cout << "--- Subject example ---" << std::endl;
	form = someRandomIntern.makeForm("robotomy request", "Bender");
	if (form)
	{
		Bureaucrat b("RobotomyGuy", 45);
		b.signForm(*form);
		b.executeForm(*form);
		delete form;
	}

	// Shrubbery
	std::cout << "\n--- Shrubbery ---" << std::endl;
	form = someRandomIntern.makeForm("shrubbery creation", "garden");
	if (form)
	{
		Bureaucrat b("Gardener", 137);
		b.signForm(*form);
		b.executeForm(*form);
		delete form;
	}

	// Presidential pardon
	std::cout << "\n--- Presidential pardon ---" << std::endl;
	form = someRandomIntern.makeForm("presidential pardon", "Marvin");
	if (form)
	{
		Bureaucrat b("Zaphod", 5);
		b.signForm(*form);
		b.executeForm(*form);
		delete form;
	}

	// Unknown form name
	std::cout << "\n--- Unknown form ---" << std::endl;
	form = someRandomIntern.makeForm("coffee request", "Intern");
	if (!form)
		std::cout << "No form was created." << std::endl;

	return 0;
}
