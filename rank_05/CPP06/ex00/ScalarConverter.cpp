#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <limits>
#include <cctype>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

static bool isSpecialDouble(const std::string &s)
{
	return s == "nan" || s == "+inf" || s == "-inf";
}

static bool isSpecialFloat(const std::string &s)
{
	return s == "nanf" || s == "+inff" || s == "-inff";
}

static bool isCharLiteral(const std::string &s)
{
	if (s.length() == 1 && !isdigit(static_cast<unsigned char>(s[0])))
		return true;
	if (s.length() == 3 && s[0] == '\'' && s[2] == '\'')
		return true;
	return false;
}

static bool isFloatLiteral(const std::string &s)
{
	return !s.empty() && s[s.length() - 1] == 'f';
}

static bool isDoubleLiteral(const std::string &s)
{
	return s.find('.') != std::string::npos;
}

static void printChar(double val)
{
	if (std::isnan(val) || std::isinf(val))
		std::cout << "char: impossible" << std::endl;
	else if (val < 0 || val > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!isprint(static_cast<int>(val)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(val) << "'" << std::endl;
}

static void printInt(double val)
{
	if (std::isnan(val) || std::isinf(val))
		std::cout << "int: impossible" << std::endl;
	else if (val < static_cast<double>(INT_MIN) || val > static_cast<double>(INT_MAX))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(val) << std::endl;
}

static void printFloat(double val)
{
	if (std::isnan(val))
		std::cout << "float: nanf" << std::endl;
	else if (std::isinf(val))
		std::cout << "float: " << (val > 0 ? "+inff" : "-inff") << std::endl;
	else
		std::cout << "float: " << std::fixed << std::setprecision(1)
			<< static_cast<float>(val) << "f" << std::endl;
}

static void printDouble(double val)
{
	if (std::isnan(val))
		std::cout << "double: nan" << std::endl;
	else if (std::isinf(val))
		std::cout << "double: " << (val > 0 ? "+inf" : "-inf") << std::endl;
	else
		std::cout << "double: " << std::fixed << std::setprecision(1) << val << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
	double val;

	if (isSpecialDouble(literal))
	{
		if (literal == "nan")
			val = std::numeric_limits<double>::quiet_NaN();
		else if (literal == "+inf")
			val = std::numeric_limits<double>::infinity();
		else
			val = -std::numeric_limits<double>::infinity();
	}
	else if (isSpecialFloat(literal))
	{
		if (literal == "nanf")
			val = static_cast<double>(std::numeric_limits<float>::quiet_NaN());
		else if (literal == "+inff")
			val = static_cast<double>(std::numeric_limits<float>::infinity());
		else
			val = static_cast<double>(-std::numeric_limits<float>::infinity());
	}
	else if (isCharLiteral(literal))
	{
		char c = (literal.length() == 1) ? literal[0] : literal[1];
		val = static_cast<double>(c);
	}
	else if (isFloatLiteral(literal))
	{
		std::string withoutF = literal.substr(0, literal.length() - 1);
		val = std::strtod(withoutF.c_str(), NULL);
	}
	else if (isDoubleLiteral(literal))
	{
		val = std::strtod(literal.c_str(), NULL);
	}
	else
	{
		val = static_cast<double>(std::strtol(literal.c_str(), NULL, 10));
	}

	printChar(val);
	printInt(val);
	printFloat(val);
	printDouble(val);
}
