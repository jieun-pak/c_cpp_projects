#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));

	// ShrubberyCreationForm: sign 145, exec 137
	{
		std::cout << "--- ShrubberyCreationForm ---" << std::endl;
		Bureaucrat b("Gardener", 137);
		ShrubberyCreationForm f("home");
		b.signForm(f);
		b.executeForm(f);
	}

	// RobotomyRequestForm: sign 72, exec 45
	{
		std::cout << "\n--- RobotomyRequestForm ---" << std::endl;
		Bureaucrat b("Robotomist", 45);
		RobotomyRequestForm f("Bender");
		b.signForm(f);
		b.executeForm(f);
		b.executeForm(f); // run twice to show randomness
	}

	// PresidentialPardonForm: sign 25, exec 5
	{
		std::cout << "\n--- PresidentialPardonForm ---" << std::endl;
		Bureaucrat b("President", 5);
		PresidentialPardonForm f("Arthur Dent");
		b.signForm(f);
		b.executeForm(f);
	}

	// Execute without signing
	{
		std::cout << "\n--- Execute unsigned form ---" << std::endl;
		Bureaucrat b("Bob", 1);
		PresidentialPardonForm f("Nobody");
		b.executeForm(f);
	}

	// Grade too low to execute
	{
		std::cout << "\n--- Grade too low to execute ---" << std::endl;
		Bureaucrat signer("Signer", 25);
		Bureaucrat lowGuy("LowGuy", 100);
		PresidentialPardonForm f("Target");
		signer.signForm(f);
		lowGuy.executeForm(f);
	}

	return 0;
}
