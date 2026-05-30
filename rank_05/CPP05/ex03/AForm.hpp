#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <stdexcept>

class Bureaucrat;

class AForm
{
public:
	AForm(const std::string &name, int gradeToSign, int gradeToExecute);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	virtual ~AForm();

	const std::string	&getName() const;
	bool				isSigned() const;
	int					getGradeToSign() const;
	int					getGradeToExecute() const;

	void	beSigned(const Bureaucrat &b);
	void	execute(Bureaucrat const &executor) const;

	class GradeTooHighException : public std::exception {
	public:
		const char *what() const throw();
	};
	class GradeTooLowException : public std::exception {
	public:
		const char *what() const throw();
	};
	class FormNotSignedException : public std::exception {
	public:
		const char *what() const throw();
	};

protected:
	virtual void executeAction() const = 0;

private:
	const std::string	_name;
	bool				_signed;
	const int			_gradeToSign;
	const int			_gradeToExecute;
};

std::ostream &operator<<(std::ostream &os, const AForm &f);

#endif
