NAME = push_swap
BONUS_NAME = checker

source = push_swap.c push_swap_utils.c operations.c
object = $(source:.c=.o)

bonus_source = checker.c push_swap_utils.c operations.c
bonus_object = $(bonus_source:.c=.o)

FLAGS = #-Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(object)
	gcc $(object) -L./libft -lft -o $(NAME)

bonus: $(bonus_object)
	gcc $(bonus_object) -L./libft -lft -o $(BONUS_NAME)

clean: 
	rm -f $(object)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o:%.c
	cc $(FLAGS) -c $< -o $@ 