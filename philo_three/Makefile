.DEFAULT_GOAL := all
# Include file
# **************************************************************************** #
# 									c									   	   #
# **************************************************************************** #
NAME = philo_two
# Libft ASM project files
FILE_SRC = philo_two.c ft_parse.c utils.c ft_fucklanorme.c ft_job.c
FILE_OBJ = $(FILE_SRC:.c=.o)
# **************************************************************************** #
# 								Building Rules								   #
# **************************************************************************** #
# Rule to build both executables
all: $(NAME)
# Rule to build Nm
$(NAME): $(FILE_SRC)
	gcc -Wall -Wextra -Werror -g3 $(FILE_SRC) -o $(NAME)
	@echo "\033[0;32m[UPDATE] \033[0m \033[1;30m CREATED:\033[0m \033 \033[0m \033[0;36m philo_two\033[0m" $(shell ls -la | grep libasm | rev | cut -d " " -f 4 | rev) $(shell ls -la | grep libasm | rev | cut -d " " -f 3 | rev) $(shell ls -la | grep libasm | rev | cut -d " " -f 2 | rev)

# **************************************************************************** #
# 								Cleaning Rules								   #
# **************************************************************************** #
clean:
	@rm -rf $(FILE_OBJ)
	@echo "\033[0;32m[UPDATE] \033[0m \033[1;30m REMOVE:\033[0m \033 \033[0m \033[0;31m *.o\033[0m \033"
fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;32m[UPDATE] \033[0m \033[1;30m REMOVE:\033[0m \033 \033[0m \033[0;31m philo_two\033[0m \033"
re: fclean all

.PHONY: all clean fclean