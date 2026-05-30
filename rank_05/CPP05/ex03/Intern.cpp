#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}
Intern::Intern(const Intern &) {}
Intern &Intern::operator=(const Intern &) { return *this; }
Intern::~Intern() {}

// Each creator is a tiny free function — no if/else chain needed
static AForm *makeShrubbery(const std::string &target)
{
	return new ShrubberyCreationForm(target);
}

static AForm *makeRobotomy(const std::string &target)
{
	return new RobotomyRequestForm(target);
}

static AForm *makePardon(const std::string &target)
{
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const
{
	struct FormEntry
	{
		const char	*name;
		AForm		*(*create)(const std::string &);
	};

	static const FormEntry table[] = {
		{ "shrubbery creation", makeShrubbery },
		{ "robotomy request",   makeRobotomy  },
		{ "presidential pardon", makePardon   }
	};
	static const int tableSize = 3;

	for (int i = 0; i < tableSize; ++i)
	{
		if (name == table[i].name)
		{
			std::cout << "Intern creates " << name << std::endl;
			return table[i].create(target);
		}
	}

	std::cerr << "Intern: unknown form name '" << name << "'" << std::endl;
	return NULL;
}
