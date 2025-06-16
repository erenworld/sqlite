##
## EREN TURKOGLU, 2025
## Makefile
## File description:
## Makefile
##

# Sources and objects
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)

# Compiler and flags
CC      = gcc
CFLAGS  = -std=c99 \
          -Wall -Wextra -Wpedantic \
          -Wshadow -Wconversion -Wsign-conversion \
          -Wuninitialized -Winit-self \
          -Wfloat-equal -Wundef -Wcast-align -Wcast-qual \
          -Wno-unused-parameter \
          -fsanitize=address \
          -fPIE \
          -fno-omit-frame-pointer \
          -g

LDFLAGS = -fsanitize=address \

# Output binary name
NAME    = sqlite

# Colors
RED     = \033[0;31m
YELLOW  = \033[0;33m
PURPLE  = \033[0;35m
GRAY1   = \033[0;37m
GRAY2   = \033[0;90m
RESET   = \033[0m

# Link rule
$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(PURPLE)[SUCCESS] :\\n  $(GRAY1)|-> Compilation completed!$(RESET)"

# Default rule
all: $(NAME)

# Compilation of object files
%.o: %.c
	@echo "$(YELLOW)[COMPILED]:\\n  $(GRAY1)|-> [file.c] $(GRAY2)$<\\n  $(GRAY1)|-> [file.o] $(GRAY2)$@$(RESET)"
	@$(CC) -c $< -o $@ $(CFLAGS)

# Cleanup rules
clean:
	@rm -f $(OBJ)
	@echo "$(RED)[CLEANED] :\\n  $(GRAY1)|-> Object files removed!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[FCLEANED] :\\n  $(GRAY1)|-> Executable removed!$(RESET)"

# Full rebuild
re: fclean all

.PHONY: all clean fclean re
