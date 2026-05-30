# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# Target executable
NAME		= Materia

# Source files
SRCS		= main.cpp \
			  AMateria.cpp \
			  Ice.cpp \
			  Cure.cpp \
			  Character.cpp \
			  MateriaSource.cpp

# Object files
OBJS		= $(SRCS:.cpp=.o)

# Header files
HEADERS		= AMateria.hpp \
			  ICharacter.hpp \
			  Ice.hpp \
			  Cure.hpp \
			  Character.hpp \
			  IMateriaSource.hpp \
			  MateriaSource.hpp

# Colors for output
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Default target
all: $(NAME)

# Link object files to create executable
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully$(RESET)"

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN)✓ Compiled $<$(RESET)"

# Clean object files
clean:
	@rm -f $(OBJS)
	@echo "$(RED)✗ Object files removed$(RESET)"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
