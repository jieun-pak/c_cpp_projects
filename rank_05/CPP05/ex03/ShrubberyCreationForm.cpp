#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other), _target(other._target) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::executeAction() const
{
	std::ofstream ofs((_target + "_shrubbery").c_str());
	if (!ofs)
		throw std::runtime_error("cannot open output file");
	ofs << "          *        \n"
		   "         ***       \n"
		   "        *****      \n"
		   "       *******     \n"
		   "      *********    \n"
		   "     ***********   \n"
		   "    *************  \n"
		   "          |        \n"
		   "          |        \n"
		   "     *        *    \n"
		   "    ***      ***   \n"
		   "   *****    *****  \n"
		   "     |        |    \n"
		   "     |        |    \n";
}
