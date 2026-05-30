#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./convert <literal>" << std::endl;
		return 1;
	}

	std::cout << "===========[Input: " << argv[1] << "]===========" << std::endl;
	ScalarConverter::convert(argv[1]);

	std::cout << std::endl;
	std::cout << "===========[Test: char 'a']===========" << std::endl;
	ScalarConverter::convert("'a'");

	std::cout << std::endl;
	std::cout << "===========[Test: int 0]===========" << std::endl;
	ScalarConverter::convert("0");

	std::cout << std::endl;
	std::cout << "===========[Test: int 42]===========" << std::endl;
	ScalarConverter::convert("42");

	std::cout << std::endl;
	std::cout << "===========[Test: int -42]===========" << std::endl;
	ScalarConverter::convert("-42");

	std::cout << std::endl;
	std::cout << "===========[Test: float 42.0f]===========" << std::endl;
	ScalarConverter::convert("42.0f");

	std::cout << std::endl;
	std::cout << "===========[Test: float -4.2f]===========" << std::endl;
	ScalarConverter::convert("-4.2f");

	std::cout << std::endl;
	std::cout << "===========[Test: double 4.2]===========" << std::endl;
	ScalarConverter::convert("4.2");

	std::cout << std::endl;
	std::cout << "===========[Test: pseudo-literal nan]===========" << std::endl;
	ScalarConverter::convert("nan");

	std::cout << std::endl;
	std::cout << "===========[Test: pseudo-literal nanf]===========" << std::endl;
	ScalarConverter::convert("nanf");

	std::cout << std::endl;
	std::cout << "===========[Test: pseudo-literal +inf]===========" << std::endl;
	ScalarConverter::convert("+inf");

	std::cout << std::endl;
	std::cout << "===========[Test: pseudo-literal -inff]===========" << std::endl;
	ScalarConverter::convert("-inff");

	std::cout << std::endl;
	std::cout << "===========[Test: non-displayable char (ASCII 1)]===========" << std::endl;
	ScalarConverter::convert("1");

	return 0;
}
