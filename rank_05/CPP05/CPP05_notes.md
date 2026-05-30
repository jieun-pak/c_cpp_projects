# CPP05 — Repetition and Exceptions

## Core Concept: C++ Exceptions

C++ exceptions let you signal and handle error conditions without checking return codes at every call site.

```cpp
throw SomeException();                              // raise
try { ... } catch (std::exception &e) { ... }       // catch
```

The subject forces you to implement exception classes **nested inside** other classes — a common real-world pattern.

---

## Exercise 00 — `Bureaucrat` (ex00/)

### Files
`Bureaucrat.hpp` · `Bureaucrat.cpp` · `main.cpp` · `Makefile`

### Class rules

| Attribute | Type | Rule |
|-----------|------|------|
| `_name` | `const std::string` | Set once at construction, never changed |
| `_grade` | `int` | Valid range: **1 (highest) … 150 (lowest)** |

- Constructor throws immediately if the grade is out of range.
- `incrementGrade()` — decreases the integer (grade 3 → 2). Throws if it would go below 1.
- `decrementGrade()` — increases the integer (grade 3 → 4). Throws if it would exceed 150.

### Nested exception classes

```cpp
class GradeTooHighException : public std::exception {
    const char *what() const throw();
};
class GradeTooLowException : public std::exception {
    const char *what() const throw();
};
```

> Exception classes do **not** need to follow Orthodox Canonical Form (subject note).

### `operator<<` output

```
Alice, bureaucrat grade 42.
```

### Key note
`throw()` after `what()` is the C++98 no-throw specifier (replaced by `noexcept` in C++11).

---

## Exercise 01 — `Form` (ex01/)

### Files added
`Form.hpp` · `Form.cpp` · updated `Bureaucrat.hpp/.cpp`

### Form attributes (all private)

| Attribute | Type | Notes |
|-----------|------|-------|
| `_name` | `const std::string` | Set at construction |
| `_signed` | `bool` | Starts `false` |
| `_gradeToSign` | `const int` | Grade needed to sign |
| `_gradeToExecute` | `const int` | Grade needed to execute |

Both grade thresholds follow the same 1–150 rule and throw `Form::GradeTooHighException` / `Form::GradeTooLowException` if invalid.

### `beSigned(const Bureaucrat &b)`

```cpp
if (b.getGrade() > _gradeToSign)   // lower number = higher grade
    throw GradeTooLowException();
_signed = true;
```

### `Bureaucrat::signForm(Form &form)`

Wraps `beSigned` in try/catch and prints:

```
Alice signed Pension
Bob couldn't sign Top Secret because form grade too low
```

---

## Exercise 02 — Abstract `AForm` + Concrete Forms (ex02/)

### Files added / changed
`AForm.hpp/.cpp` (replaces `Form`) · `ShrubberyCreationForm.hpp/.cpp` · `RobotomyRequestForm.hpp/.cpp` · `PresidentialPardonForm.hpp/.cpp` · updated `Bureaucrat`

### AForm is abstract

`AForm` has a **pure virtual** protected method `executeAction()`. Concrete classes implement it; the base class `execute()` validates then calls it — the elegant single-responsibility design the subject hints at:

```cpp
// AForm.cpp
void AForm::execute(Bureaucrat const &executor) const
{
    if (!_signed)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    executeAction();   // dispatches to concrete class
}
```

All validation lives in one place. Concrete classes only implement the action, not the guard.

### New exception
`AForm::FormNotSignedException` — thrown by `execute()` when `_signed == false`.

### Concrete form table

| Class | gradeToSign | gradeToExecute | Action |
|-------|------------|----------------|--------|
| `ShrubberyCreationForm` | 145 | 137 | Creates `<target>_shrubbery` file with ASCII trees |
| `RobotomyRequestForm` | 72 | 45 | Drills, then 50% success via `std::rand()` |
| `PresidentialPardonForm` | 25 | 5 | Prints pardon by Zaphod Beeblebrox |

All constructors take only one parameter: `target`.

### `Bureaucrat::executeForm(AForm const &form) const`

```
Alice executed ShrubberyCreationForm
Bob couldn't execute PresidentialPardonForm because form grade too low
```

---

## Exercise 03 — `Intern` (ex03/)

### Files added
`Intern.hpp` · `Intern.cpp`

### What the Intern does

```cpp
AForm *makeForm(const std::string &name, const std::string &target) const;
```

Returns a heap-allocated `AForm*` matching the requested form name, or `NULL` with an error message if the name is unknown.

```
Intern creates robotomy request
```

### The key design constraint: no if/else chain

The subject explicitly bans `if/else if` ladders for the form lookup. The clean solution is a **dispatch table** — an array of structs pairing a name string with a creator function pointer:

```cpp
struct FormEntry {
    const char  *name;
    AForm       *(*create)(const std::string &);
};

static const FormEntry table[] = {
    { "shrubbery creation",  makeShrubbery },
    { "robotomy request",    makeRobotomy  },
    { "presidential pardon", makePardon    }
};
```

A single loop over the table replaces all branching. Adding a new form type means adding one row — no logic changes.

### Memory note
`makeForm` returns a raw `new`-allocated pointer. The **caller owns it** and must `delete` it after use to avoid a leak.

---

## Grade comparison rule (critical)

> Grade **1** is the **highest**. Grade **150** is the **lowest**.

`bureaucrat.grade <= form.gradeRequired` = bureaucrat is senior enough.  
Always detect "too low" with `>`:

```cpp
if (b.getGrade() > _gradeToSign)
    throw GradeTooLowException();
```

---

## Orthodox Canonical Form (OCF) checklist

Every class (except exception classes) must have:

1. Constructor
2. Copy constructor
3. Copy-assignment operator
4. Destructor

For classes with `const` members (`_name`, `_gradeToSign`, `_gradeToExecute`), copy-assignment can only copy the non-const members (`_grade`, `_signed`). This is valid C++98.

---

## Compilation

```bash
cd ex00 && make && ./bureaucrat
cd ex01 && make && ./form
cd ex02 && make && ./aform
cd ex03 && make && ./intern
```

All use: `c++ -Wall -Wextra -Werror -std=c++98`

---

## Common mistakes to avoid

| Mistake | Fix |
|---------|-----|
| Using `>= gradeToSign` in `beSigned` | Bureaucrat with **equal** grade is allowed — use `>` |
| Checking grade/signed inside each concrete `execute` | Do it once in `AForm::execute()`, call `executeAction()` after |
| Using if/else chain in `Intern::makeForm` | Use a dispatch table (array of function pointers) |
| Forgetting to `delete` the pointer returned by `makeForm` | Caller owns the heap object |
| Forgetting include guards | Always add `#ifndef` guards — double inclusion = grade 0 |
| Putting function bodies in headers | All implementations go in `.cpp` files |
| Using `std::vector`, `std::map`, etc. | STL containers are forbidden until CPP08 |
| `using namespace std;` | Forbidden — use `std::` prefix everywhere |
