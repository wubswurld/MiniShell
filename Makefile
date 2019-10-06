NAME = minishell

CFILES = main.c parse.c expansions.c builtin.c builtin2.c helpers.c

FLAGS = -Wall -Werror -Wextra -g
#  -fsanitize=address

LIBFT = libft

GCC = gcc

all: $(NAME)

$(NAME):
	@echo "\033[32mCompiling files . . .\033[0;33m"
	@make -C $(LIBFT)
	$(GCC) $(FLAGS) $(CFILES) -L $(LIBFT) -lft -o $(NAME) 

clean:
	@echo "\033[32mCleaning .\033[0;33m"
	@rm -rf $(NAME)
	@make clean -C $(LIBFT)

fclean: clean
	@echo "\033[32mClean more . .\033[0;33m"
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean all re